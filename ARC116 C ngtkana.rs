#[allow(unused_imports)]
#[cfg(feature = "dbg")]
use dbg::lg;
use erato::LpdSieve;
use fp::F998244353 as Fp;
use itertools::Itertools;
use proconio::input;

fn main() {
    input! { seq_len: usize, number_max: usize }
    let fact_len = 2 * (seq_len + number_max) + 1;
    let mut fact = (0..fact_len).map(Fp::from).collect_vec();
    fact[0] = Fp::new(1);
    accum::mul(&mut fact);
    let mut fact_recip = (1..=fact_len).map(Fp::from).collect_vec();
    fact_recip[fact_len - 1] = fact[fact_len - 1].recip();
    for i in (0..fact_len - 1).rev() {
        fact_recip[i] = fact_recip[i + 1] * Fp::from(i + 1);
    }
    let binom = |seq_len: usize, i: usize| -> Fp {
        fact[seq_len] * fact_recip[i] * fact_recip[seq_len - i]
    };

    let mut sieve = LpdSieve::new();
    let divisors = (0..=number_max)
        .map(|x| {
            if x == 0 {
                Vec::new()
            } else {
                sieve.prime_factors(x).rle().collect_vec()
            }
        })
        .collect_vec();
    let mut dp = divisors
        .iter()
        .map(|v| {
            v.iter()
                .map(|&(_, x)| binom(seq_len + x, x))
                .product::<Fp>()
        })
        .collect_vec();

    for p in sieve
        .prime_numbers()
        .take_while(|&p: &usize| p <= number_max)
    {
        for i in (1..=number_max / p).rev() {
            let sub = dp[i];
            dp[i * p] -= sub;
        }
    }
    let ans = dp[1..].iter().sum::<Fp>();
    println!("{}", ans);
}

// erato {{{
#[allow(dead_code)]
mod erato {

    mod converters {
        use {
            super::{Int, PrimeFactorsByLookup, PrimeFactorsByTrialDivision},
            std::{iter::Peekable, marker::PhantomData},
        };

        pub trait PrimeFactors<T: Int>: Sized + Iterator<Item = T> {
            fn unique(self) -> Unique<T, Self> {
                Unique {
                    iter: self,
                    prev: None,
                }
            }
            fn rle(self) -> Rle<T, Self> {
                Rle {
                    iter: self.peekable(),
                    _marker: PhantomData,
                }
            }
        }
        impl<'a, T: Int> PrimeFactors<T> for PrimeFactorsByTrialDivision<'a, T> {}
        impl<'a, T: Int> PrimeFactors<T> for PrimeFactorsByLookup<'a, T> {}

        pub struct Unique<T: Int, P: PrimeFactors<T>> {
            iter: P,
            prev: Option<T>,
        }
        impl<T: Int, P: PrimeFactors<T>> Iterator for Unique<T, P> {
            type Item = P::Item;
            fn next(&mut self) -> Option<Self::Item> {
                let prev = self.prev;
                let res = self.iter.find(|&p| Some(p) != prev);
                self.prev = res;
                res
            }
        }

        pub struct Rle<T: Int, P: PrimeFactors<T>> {
            iter: Peekable<P>,
            _marker: PhantomData<T>,
        }
        impl<'a, T: Int, P: PrimeFactors<T>> Iterator for Rle<T, P> {
            type Item = (P::Item, usize);
            fn next(&mut self) -> Option<Self::Item> {
                if let Some(p) = self.iter.next() {
                    let mut multi = 1;
                    while self.iter.peek() == Some(&p) {
                        multi += 1;
                        self.iter.next();
                    }
                    Some((p, multi))
                } else {
                    None
                }
            }
        }
    }
    mod int {
        use std::{
            fmt::Debug,
            ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Rem, RemAssign, Sub, SubAssign},
        };

        pub trait Int:
            Debug
            + Copy
            + Ord
            + Add<Output = Self>
            + AddAssign
            + Sub<Output = Self>
            + SubAssign
            + Mul<Output = Self>
            + MulAssign
            + Div<Output = Self>
            + DivAssign
            + Rem<Output = Self>
            + RemAssign
        {
            fn zero() -> Self;
            fn one() -> Self;
            fn two() -> Self;
            fn as_usize(self) -> usize;
            fn from_usize(src: usize) -> Self;
        }

        macro_rules! impl_int {
            ($($t:ty),* $(,)?) => {$(
                impl Int for $t {
                    fn zero() -> Self {
                        0
                    }
                    fn one() -> Self {
                        1
                    }
                    fn two() -> Self {
                        2
                    }
                    fn as_usize(self) -> usize {
                        self as usize
                    }
                    fn from_usize(src: usize) -> Self {
                        src as Self
                    }
                }
            )*}
        }
        impl_int! {
            usize, u8, u16, u32, u64, u128,
            isize, i8, i16, i32, i64, i128,
        }
    }
    mod lpd_sieve {
        use super::{
            sieve_base::{PrimeFactorsByLookup, PrimeNumbers},
            sieve_kind, Int, SieveBase,
        };

        #[derive(Default, Debug, Clone, PartialEq)]
        pub struct LpdSieve {
            base: SieveBase<sieve_kind::Usize>,
        }

        impl LpdSieve {
            pub fn new() -> Self {
                Self {
                    base: SieveBase::new(),
                }
            }
            pub fn is_empty(&self) -> bool {
                self.base.is_empty()
            }
            pub fn len(&self) -> usize {
                self.base.len()
            }
            pub fn with_len(n: usize) -> Self {
                Self {
                    base: SieveBase::with_len(n),
                }
            }
            pub fn is_prime<T: Int>(&mut self, x: T) -> bool {
                self.base.is_prime(x)
            }
            pub fn lpd<T: Int>(&mut self, x: T) -> T {
                self.base.lpd(x)
            }
            pub fn prime_numbers<T: Int>(&mut self) -> PrimeNumbers<sieve_kind::Usize, T> {
                self.base.prime_numbers()
            }
            pub fn prime_factors<T: Int>(&mut self, n: T) -> PrimeFactorsByLookup<T> {
                self.base.prime_factors_by_lookup(n)
            }
        }
    }
    mod sieve {
        use super::{
            sieve_base::{PrimeFactorsByTrialDivision, PrimeNumbers},
            sieve_kind, Int, SieveBase,
        };

        #[derive(Default, Debug, Clone, PartialEq)]
        pub struct Sieve {
            base: SieveBase<sieve_kind::Boolean>,
        }

        impl Sieve {
            pub fn new() -> Self {
                Self {
                    base: SieveBase::new(),
                }
            }
            pub fn is_empty(&self) -> bool {
                self.base.is_empty()
            }
            pub fn len(&self) -> usize {
                self.base.len()
            }
            pub fn with_len(n: usize) -> Self {
                Self {
                    base: SieveBase::with_len(n),
                }
            }
            pub fn is_prime<T: Int>(&mut self, x: T) -> bool {
                self.base.is_prime(x)
            }
            pub fn prime_numbers<T: Int>(&mut self) -> PrimeNumbers<sieve_kind::Boolean, T> {
                self.base.prime_numbers()
            }
            pub fn prime_factors<T: Int>(&mut self, n: T) -> PrimeFactorsByTrialDivision<T> {
                self.base.prime_factors_by_trial_division(n)
            }
        }
    }
    mod sieve_base {
        use {
            super::{
                sieve_kind::{self, SieveKind},
                Int, PrimeFactors, Rle, Unique,
            },
            std::marker::PhantomData,
        };

        #[derive(Debug, Clone, PartialEq)]
        pub struct SieveBase<S: SieveKind> {
            sieve: Vec<S::SieveValue>,
            list: Vec<usize>,
        }

        impl<S: SieveKind> SieveBase<S> {
            pub fn new() -> Self {
                Self {
                    sieve: S::new(),
                    list: Vec::new(),
                }
            }
            pub fn is_empty(&self) -> bool {
                self.sieve.is_empty()
            }
            pub fn len(&self) -> usize {
                self.sieve.len()
            }
            pub fn with_len(n: usize) -> Self {
                let sieve = S::construct(n);
                let list = sieve
                    .iter()
                    .enumerate()
                    .filter(|&(index, &b)| S::is_prime(index, b))
                    .map(|(index, _)| index)
                    .collect();
                Self { sieve, list }
            }
            pub fn is_prime<T: Int>(&mut self, x: T) -> bool {
                assert!(T::zero() <= x);
                let x = x.as_usize();
                if self.sieve.len() <= x {
                    *self = Self::with_len(x + 1);
                }
                S::is_prime(x, self.sieve[x.as_usize()])
            }
            pub fn prime_numbers<T: Int>(&mut self) -> PrimeNumbers<S, T> {
                PrimeNumbers {
                    sieve: self,
                    index: 0,
                    _marker: PhantomData,
                }
            }
            fn extend(&mut self, len: usize) {
                assert!(2 * self.len() <= len);
                *self = Self::with_len(len);
            }
        }

        impl<S: SieveKind> Default for SieveBase<S> {
            fn default() -> Self {
                Self::new()
            }
        }

        impl SieveBase<sieve_kind::Boolean> {
            pub fn prime_factors_by_trial_division<T: Int>(
                &mut self,
                n: T,
            ) -> PrimeFactorsByTrialDivision<T> {
                assert!(T::zero() < n);
                let mut prime_numbers = self.prime_numbers();
                PrimeFactorsByTrialDivision {
                    p: prime_numbers.next().unwrap(),
                    prime_numbers,
                    n,
                }
            }
        }

        pub struct PrimeNumbers<'a, S: SieveKind, T: Int> {
            sieve: &'a mut SieveBase<S>,
            index: usize,
            _marker: PhantomData<T>,
        }

        pub struct PrimeFactorsByTrialDivision<'a, T: Int> {
            prime_numbers: PrimeNumbers<'a, sieve_kind::Boolean, T>,
            p: T,
            n: T,
        }
        impl<'a, S: SieveKind, T: Int> Iterator for PrimeNumbers<'a, S, T> {
            type Item = T;
            fn next(&mut self) -> Option<Self::Item> {
                let Self { sieve, index, .. } = self;
                let p = if let Some(&p) = sieve.list.get(*index) {
                    T::from_usize(p)
                } else {
                    sieve.extend((sieve.len() * 2).max(3));
                    T::from_usize(sieve.list[*index])
                };
                *index += 1;
                Some(p)
            }
        }
        impl<T: Int> PrimeFactorsByTrialDivision<'_, T> {
            pub fn unique(self) -> Unique<T, Self> {
                PrimeFactors::unique(self)
            }
            pub fn rle(self) -> Rle<T, Self> {
                PrimeFactors::rle(self)
            }
        }
        impl<'a, T: Int> Iterator for PrimeFactorsByTrialDivision<'a, T> {
            type Item = T;
            fn next(&mut self) -> Option<Self::Item> {
                let Self {
                    prime_numbers,
                    p,
                    n,
                } = self;
                if *n == T::one() {
                    None
                } else {
                    while *n % *p != T::zero() {
                        if *n <= *p * *p {
                            *p = *n;
                            break;
                        }
                        *p = prime_numbers.next().unwrap();
                    }
                    *n /= *p;
                    Some(*p)
                }
            }
        }

        pub struct PrimeFactorsByLookup<'a, T: Int> {
            sieve: &'a mut SieveBase<sieve_kind::Usize>,
            n: T,
        }
        impl SieveBase<sieve_kind::Usize> {
            pub fn prime_factors_by_lookup<T: Int>(&mut self, n: T) -> PrimeFactorsByLookup<T> {
                assert!(T::zero() < n);
                PrimeFactorsByLookup { sieve: self, n }
            }
            pub fn lpd<T: Int>(&mut self, n: T) -> T {
                let n = n.as_usize();
                if self.sieve.len() <= n {
                    self.extend(2 * (n + 1));
                }
                T::from_usize(self.sieve[n])
            }
        }
        impl<T: Int> PrimeFactorsByLookup<'_, T> {
            pub fn unique(self) -> Unique<T, Self> {
                PrimeFactors::unique(self)
            }
            pub fn rle(self) -> Rle<T, Self> {
                PrimeFactors::rle(self)
            }
        }
        impl<'a, T: Int> Iterator for PrimeFactorsByLookup<'a, T> {
            type Item = T;
            fn next(&mut self) -> Option<Self::Item> {
                let Self { sieve, n } = self;
                if *n == T::one() {
                    None
                } else {
                    let p = sieve.lpd(*n);
                    *n /= p;
                    Some(p)
                }
            }
        }
    }
    mod sieve_kind {
        pub trait SieveKind {
            type SieveValue: Copy;
            fn new() -> Vec<Self::SieveValue>;
            fn construct(len: usize) -> Vec<Self::SieveValue>;
            fn is_prime(index: usize, b: Self::SieveValue) -> bool;
        }

        #[derive(Debug, Clone, Copy, PartialEq)]
        pub enum Boolean {}
        #[derive(Debug, Clone, Copy, PartialEq)]
        pub enum Usize {}

        impl SieveKind for Boolean {
            type SieveValue = bool;
            fn new() -> Vec<Self::SieveValue> {
                Vec::new()
            }
            fn construct(len: usize) -> Vec<Self::SieveValue> {
                construct_is_prime_table(len)
            }
            fn is_prime(_index: usize, b: Self::SieveValue) -> bool {
                b
            }
        }

        impl SieveKind for Usize {
            type SieveValue = usize;
            fn new() -> Vec<Self::SieveValue> {
                Vec::new()
            }
            fn construct(len: usize) -> Vec<Self::SieveValue> {
                construct_lpd_table(len)
            }
            fn is_prime(index: usize, b: Self::SieveValue) -> bool {
                index == b
            }
        }

        pub fn construct_is_prime_table(n: usize) -> Vec<bool> {
            let mut is_prime = vec![true; n];
            (0..2.min(n)).for_each(|i| is_prime[i] = false);
            for p in (2..).take_while(|&p| p * p < n) {
                if !is_prime[p] {
                    continue;
                }
                let mut i = p * p;
                while i < n {
                    is_prime[i] = false;
                    i += p;
                }
            }
            is_prime
        }

        fn construct_lpd_table(n: usize) -> Vec<usize> {
            let mut lpd = vec![std::usize::MAX; n];
            for p in 2..n {
                if lpd[p] != std::usize::MAX {
                    continue;
                }
                lpd[p] = p;
                let mut i = p * p;
                while i < n {
                    if lpd[i] == std::usize::MAX {
                        lpd[i] = p;
                    }
                    i += p;
                }
            }
            lpd
        }
    }

    pub use {
        converters::{PrimeFactors, Rle, Unique},
        int::Int,
        lpd_sieve::LpdSieve,
        sieve::Sieve,
        sieve_base::{PrimeFactorsByLookup, PrimeFactorsByTrialDivision, PrimeNumbers},
    };

    use sieve_base::SieveBase;
}
// }}}
// accum {{{
#[allow(dead_code)]
mod accum {
    use std::{
        cmp::Ord,
        ops::{
            AddAssign, BitAndAssign, BitOrAssign, BitXorAssign, DivAssign, MulAssign, SubAssign,
        },
    };
    pub fn add<T: Copy + AddAssign>(a: &mut [T]) {
        for_each_mut(a, |&mut x, y| *y += x);
    }
    pub fn add_inv<T: Copy + SubAssign>(a: &mut [T]) {
        rfor_each_mut(a, |&mut x, y| *y -= x);
    }
    pub fn mul<T: Copy + MulAssign>(a: &mut [T]) {
        for_each_mut(a, |&mut x, y| *y *= x);
    }
    pub fn mul_inv<T: Copy + DivAssign>(a: &mut [T]) {
        rfor_each_mut(a, |&mut x, y| *y /= x);
    }
    // -- ord
    pub fn min<T: Copy + Ord>(a: &mut [T]) {
        for_each_mut(a, |&mut x, y| *y = x.min(*y));
    }
    pub fn max<T: Copy + Ord>(a: &mut [T]) {
        for_each_mut(a, |&mut x, y| *y = x.max(*y));
    }
    // --  bit
    pub fn xor<T: Copy + BitXorAssign>(a: &mut [T]) {
        for_each_mut(a, |&mut x, y| *y ^= x);
    }
    pub fn xor_inv<T: Copy + BitXorAssign>(a: &mut [T]) {
        rfor_each_mut(a, |&mut x, y| *y ^= x);
    }
    pub fn or<T: Copy + BitOrAssign>(a: &mut [T]) {
        for_each_mut(a, |&mut x, y| *y |= x);
    }
    pub fn and<T: Copy + BitAndAssign>(a: &mut [T]) {
        for_each_mut(a, |&mut x, y| *y &= x);
    }
    // -- for_each
    pub fn for_each<T>(a: &[T], mut f: impl FnMut(&T, &T)) {
        if !a.is_empty() {
            for i in 1..a.len() {
                let (left, right) = a.split_at(i);
                f(left.last().unwrap(), right.first().unwrap());
            }
        }
    }
    pub fn rfor_each<T>(a: &[T], mut f: impl FnMut(&T, &T)) {
        if !a.is_empty() {
            for i in (1..a.len()).rev() {
                let (left, right) = a.split_at(i);
                f(left.last().unwrap(), right.first().unwrap());
            }
        }
    }
    pub fn for_each_mut<T>(a: &mut [T], mut f: impl FnMut(&mut T, &mut T)) {
        if !a.is_empty() {
            for i in 1..a.len() {
                let (left, right) = a.split_at_mut(i);
                f(left.last_mut().unwrap(), right.first_mut().unwrap());
            }
        }
    }
    pub fn rfor_each_mut<T>(a: &mut [T], mut f: impl FnMut(&mut T, &mut T)) {
        if !a.is_empty() {
            for i in (1..a.len()).rev() {
                let (left, right) = a.split_at_mut(i);
                f(left.last_mut().unwrap(), right.first_mut().unwrap());
            }
        }
    }
}
// }}}
// fp {{{
#[allow(dead_code)]
mod fp {

    use std::{
        cmp::PartialEq,
        fmt,
        hash::{Hash, Hasher},
        iter::{Product, Sum},
        marker::PhantomData,
        mem::swap,
        ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Neg, Sub, SubAssign},
    };

    pub trait Mod: Clone + Copy + Hash {
        const P: u32;
        const K: u32;
        const R2: u32 = ((1u128 << 64) % Self::P as u128) as _; // 2 ^ 64 mod P
    }
    fn reduce<M: Mod>(x: u64) -> u32 {
        ((x + M::K.wrapping_mul(x as u32) as u64 * M::P as u64) >> 32) as u32
    }

    #[macro_export]
    macro_rules! define_mod {
        ($(($Fp: ident, $Mod: ident, $mod: expr, $k: expr),)*) => {$(
            #[derive(Clone, Debug, Default, Hash, Copy)]
            pub struct $Mod {}
            impl Mod for $Mod {
                const P: u32 = $mod;
                const K: u32 = $k;
            }
            pub type $Fp = Fp<$Mod>;
        )*}
    }
    define_mod! {
        (F998244353, Mod998244353, 998_244_353, 998_244_351),
        (F1000000007, Mod1000000007, 1_000_000_007, 2_226_617_417),
        (F1012924417, Mod1012924417, 1_012_924_417, 1_012_924_415),
        (F924844033, Mod924844033, 924_844_033, 924_844_031),
    }

    #[derive(Clone, Default, Copy)]
    pub struct Fp<M> {
        value: u32,
        __marker: PhantomData<M>,
    }
    impl<M: Mod> Fp<M> {
        pub const P: u32 = M::P;
        pub fn new(value: u32) -> Self {
            Fp::from_raw(reduce::<M>(value as u64 * M::R2 as u64))
        }
        pub fn value(self) -> u32 {
            let x = reduce::<M>(self.value as _);
            if M::P <= x {
                x - M::P
            } else {
                x
            }
        }
        #[allow(clippy::many_single_char_names)]
        pub fn recip(self) -> Self {
            assert_ne!(self, Fp::new(0), "0 はだめ。");
            let mut x = M::P as i32;
            let mut y = self.value() as i32;
            let mut u = 0;
            let mut v = 1;
            while y != 0 {
                let q = x / y;
                x -= q * y;
                u -= q * v;
                swap(&mut x, &mut y);
                swap(&mut u, &mut v);
            }
            debug_assert_eq!(x, 1);
            if u < 0 {
                debug_assert_eq!(v, M::P as i32);
                u += v;
            }
            Self::new(u as u32)
        }
        pub fn pow<T: Into<u64>>(self, exp: T) -> Self {
            let mut exp = exp.into();
            if exp == 0 {
                return Fp::new(1);
            }
            let mut base = self;
            let mut acc = Fp::new(1);
            while 1 < exp {
                if exp & 1 == 1 {
                    acc *= base;
                }
                exp /= 2;
                base *= base;
            }
            acc * base
        }
        fn from_raw(value: u32) -> Self {
            Self {
                value,
                __marker: PhantomData,
            }
        }
    }
    fn simplify(value: i32, p: i32) -> (i32, i32, i32) {
        if value.abs() < 10_000 {
            (value, 1, 0)
        } else {
            let mut q = p.div_euclid(value);
            let mut r = p.rem_euclid(value);
            if value <= 2 * r {
                q += 1;
                r -= value;
            }
            let (num, pden, ppden) = simplify(r, value);
            let den = ppden - q * pden;
            (num, den, pden)
        }
    }
    macro_rules! impl_from_large_int {
        ($($T: ty), *$(,)?) => {$(
            impl<M: Mod> From<$T> for Fp<M> {
                fn from(x: $T) -> Self {
                    Self::new(x.rem_euclid(M::P as _) as u32)
                }
            }
        )*}
    }
    impl_from_large_int! {
        u32, u64, u128, usize,
        i32, i64, i128, isize,
    }
    macro_rules! impl_from_small_int {
        ($($T: ty), *$(,)?) => {$(
            impl<M: Mod> From<$T> for Fp<M> {
                fn from(x: $T) -> Self {
                    Self::new(x as u32)
                }
            }
        )*}
    }
    impl_from_small_int! {
        u8, u16,
        i8, i16,
    }

    impl<M: Mod> PartialEq for Fp<M> {
        fn eq(&self, other: &Self) -> bool {
            fn value<M: Mod>(fp: Fp<M>) -> u32 {
                if fp.value >= M::P {
                    fp.value - M::P
                } else {
                    fp.value
                }
            }
            value(*self) == value(*other)
        }
    }
    impl<M: Mod> Eq for Fp<M> {}
    impl<M: Mod> Hash for Fp<M> {
        fn hash<H: Hasher>(&self, state: &mut H) {
            self.value().hash(state);
        }
    }
    impl<M: Mod, T: Into<Fp<M>>> AddAssign<T> for Fp<M> {
        fn add_assign(&mut self, rhs: T) {
            self.value += rhs.into().value;
            if M::P * 2 <= self.value {
                self.value -= M::P * 2;
            }
        }
    }
    impl<M: Mod, T: Into<Fp<M>>> SubAssign<T> for Fp<M> {
        fn sub_assign(&mut self, rhs: T) {
            let rhs = rhs.into();
            if self.value < rhs.value {
                self.value += M::P * 2;
            }
            self.value -= rhs.value;
        }
    }
    impl<M: Mod, T: Into<Fp<M>>> MulAssign<T> for Fp<M> {
        fn mul_assign(&mut self, rhs: T) {
            self.value = reduce::<M>(self.value as u64 * rhs.into().value as u64);
        }
    }
    #[allow(clippy::suspicious_op_assign_impl)]
    impl<M: Mod, T: Into<Fp<M>>> DivAssign<T> for Fp<M> {
        fn div_assign(&mut self, rhs: T) {
            *self *= rhs.into().recip();
        }
    }

    macro_rules! forward_ops {
        ($(($trait:ident, $method_assign:ident, $method:ident),)*) => {$(
            impl<M: Mod> $trait for Fp<M> {
                type Output = Self;
                fn $method(mut self, rhs: Self) -> Self {
                    self.$method_assign(rhs);
                    self
                }
            }
            impl<'a, T: Mod> $trait<Fp<T>> for &'a Fp<T> {
                type Output = Fp<T>;
                fn $method(self, other: Fp<T>) -> Self::Output {
                    $trait::$method(*self, other)
                }
            }

            impl<'a, T: Mod> $trait<&'a Fp<T>> for Fp<T> {
                type Output = Fp<T>;
                fn $method(self, other: &Fp<T>) -> Self::Output {
                    $trait::$method(self, *other)
                }
            }

            impl<'a, T: Mod> $trait<&'a Fp<T>> for &'a Fp<T> {
                type Output = Fp<T>;
                fn $method(self, other: &Fp<T>) -> Self::Output {
                    $trait::$method(*self, *other)
                }
            }
        )*};
    }
    forward_ops! {
        (Add, add_assign, add),
        (Sub, sub_assign, sub),
        (Mul, mul_assign, mul),
        (Div, div_assign, div),
    }
    impl<M: Mod> Neg for Fp<M> {
        type Output = Self;
        fn neg(self) -> Self {
            Fp::from_raw(M::P * 2 - self.value)
        }
    }
    impl<M: Mod> Sum for Fp<M> {
        fn sum<I: Iterator<Item = Self>>(iter: I) -> Self {
            iter.fold(Self::new(0), |b, x| b + x)
        }
    }
    impl<M: Mod> Product for Fp<M> {
        fn product<I: Iterator<Item = Self>>(iter: I) -> Self {
            iter.fold(Self::new(1), |b, x| b * x)
        }
    }
    impl<'a, M: Mod> Sum<&'a Self> for Fp<M> {
        fn sum<I: Iterator<Item = &'a Self>>(iter: I) -> Fp<M> {
            iter.fold(Self::new(0), |b, x| b + x)
        }
    }
    impl<'a, M: Mod> Product<&'a Self> for Fp<M> {
        fn product<I: Iterator<Item = &'a Self>>(iter: I) -> Fp<M> {
            iter.fold(Self::new(1), |b, x| b * x)
        }
    }
    impl<M: Mod> fmt::Debug for Fp<M> {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> Result<(), std::fmt::Error> {
            let (num, den, _) = simplify(self.value() as i32, M::P as i32);
            let (num, den) = match den.signum() {
                1 => (num, den),
                -1 => (-num, -den),
                _ => unreachable!(),
            };
            if den == 1 {
                write!(f, "{}", num)
            } else {
                write!(f, "{}/{}", num, den)
            }
        }
    }
    impl<M: Mod> fmt::Display for Fp<M> {
        fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
            self.value().fmt(f)
        }
    }
}
// }}}
// template {{{
#[cfg(not(feature = "dbg"))]
#[allow(unused_macros)]
#[macro_export]
macro_rules! lg {
    ($($expr:expr),*) => {};
}
// }}}
