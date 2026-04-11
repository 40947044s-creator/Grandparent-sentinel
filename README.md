# Project NP: 2-Adic Recursive Convergence

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Researcher:** Marilyn Hsiao  
**Status:** 7EARTH ORACLE — VERIFIED  
**Domain:** [open-experiments.org](https://open-experiments.org)

## Overview
Project NP explores the unique recovery of an invariant parameter $P$ within the finite ring $\mathbb{Z}_{2^{13}}$. Unlike standard heuristic approaches, this engine utilizes a **Liar Paradox Attack** to enforce the **Grandparent Sentinel** (MSB) as a boundary condition.

## The Logic
The system leverages the deterministic nature of carry ripples in 2-adic multiplication. By testing bit hypotheses and observing their "growth" ($<<$) toward the MSB, the engine identifies and prunes "Liar" branches that contradict the observed invariant state.

### Key Axioms
* **Unit Existence Axiom:** There exists a transition where $v_2(N_t + 1) = 0$.
* **Temporal Invariance:** $P$ remains stationary over window $T \ge 2$.
* **Grandparent Sentinel:** The MSB acts as the final arbiter of truth.

## Usage
To compile the C implementation of the recovery engine:
```bash
gcc project_np.c -o project_np
./project_np
