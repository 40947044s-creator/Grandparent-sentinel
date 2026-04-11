/*
 * Project NP: Multi-Pair Extraction Demo
 * Copyright (c) 2026 Marilyn Hsiao
 * MIT License
 * * Logic: Grandparent Sentinel (Bit 59) vs. Multiple Observation Pairs
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define RING_SIZE 60
#define MODULO (1ULL << 60)
#define MSB_MASK (1ULL << (RING_SIZE - 1))
#define NUM_PAIRS 3  // We use 3 pairs to ensure the Liar has nowhere to hide

typedef struct {
    uint64_t n_val;
    uint64_t delta_np;
} NPPair;

// --- STEP 1: NP ENTER (The Simulation) ---
uint64_t transition(uint64_t p, uint64_t n) {
    return (p * (n + 1)) & (MODULO - 1);
}

// --- STEP 2: EXTRACTION (The Liar Paradox Attack) ---
uint64_t extract_with_pairs(NPPair pairs[], int num_pairs) {
    uint64_t p_guess = 0;

    printf("[7EARTH] Starting Extraction at 2^60 Scale...\n");

    for (int k = 0; k < RING_SIZE; k++) {
        bool bit_k_is_liar = false;
        uint64_t hypothesis = p_guess | (1ULL << k);

        // Check the hypothesis against ALL pairs
        for (int i = 0; i < num_pairs; i++) {
            uint64_t res = transition(hypothesis, pairs[i].n_val);
            uint64_t target_msb = pairs[i].delta_np & MSB_MASK;

            // If the growth (<<) at this bit level flips the MSB 
            // against any of our known Sentinels, it's a Liar.
            if (k == RING_SIZE - 1 && (res & MSB_MASK) != target_msb) {
                bit_k_is_liar = true;
                break;
            }
        }

        if (bit_k_is_liar) {
            printf("[SENTINEL] Bit %d: Paradox detected. Pruning branch.\n", k);
            // In a real Liar Attack, we'd do a more complex carry-reversal here
        } else {
            p_guess = hypothesis;
        }
    }

    return p_guess;
}

int main() {
    // 1. User Enters Secret (NP Enter)
    uint64_t secret_p = 123456789012345ULL; // Our hidden invariant
    uint64_t inputs[NUM_PAIRS] = {10, 42, 99};
    NPPair dataset[NUM_PAIRS];

    printf("--- PROJECT NP DEMO ---\n");
    for (int i = 0; i < NUM_PAIRS; i++) {
        dataset[i].n_val = inputs[i];
        dataset[i].delta_np = transition(secret_p, inputs[i]);
        printf("Pair %d Recorded: N=%llu, Delta=%llu\n", i, dataset[i].n_val, dataset[i].delta_np);
    }

    // 2. Extracting by filling up pairs
    uint64_t result = extract_with_pairs(dataset, NUM_PAIRS);

    printf("\n--- FINAL VERDICT ---\n");
    printf("Extracted P: %llu\n", result);
    printf("Status: %s\n", (result == secret_p) ? "VERIFIED (Axiomatic Necessity)" : "COLLISION");

    return 0;
}
