def factorial(n):
    result = 1
    for i in range(1, n + 1):
        result *= i

    return result

def comb(n, k):
    return factorial(n) // (factorial(k) * factorial(n - k))

# 1
hit_prob = 0.75

n_attacks_small = 4
k_hits = 3
prob_3_in_4 = comb(n_attacks_small, k_hits) * (hit_prob**k_hits) * ((1 - hit_prob)**(n_attacks_small - k_hits))

print("1)")
print(f"Probability that the player hits the target exactly 3 times in 4 attempts: {prob_3_in_4:.15f} ({prob_3_in_4 * 100:.2f}%)")

n_attacks_large = 100
expected_hits = n_attacks_large * hit_prob
print(f"If the player makes 100 attack attempts, expected number of successful hits: {expected_hits}")

prob_miss_at_least_30 = sum(
    comb(n_attacks_large, k) * (hit_prob**k) * ((1 - hit_prob)**(n_attacks_large - k))
    for k in range(71)
)
print(f"Probability that, in a sequence of 100 attacks, the player misses at least 30 times: {prob_miss_at_least_30:.15f}")

# 2
drop_prob = 0.05
n_enemies = 50

prob_zero_drops = comb(n_enemies, 0) * (drop_prob**0) * ((1 - drop_prob)**n_enemies)

print("2)")
print(f"Probability of exactly 0 rare item drops in 50 defeats: {prob_zero_drops:.15f} ({prob_zero_drops * 100:.2f}%)")

prob_at_least_one = 1 - prob_zero_drops
print(f"Probability of at least 1 rare item drop in 50 defeats: {prob_at_least_one:.15f} ({prob_at_least_one * 100:.2f}%)")
