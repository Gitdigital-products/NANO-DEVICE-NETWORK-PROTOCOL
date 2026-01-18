# Governance Engine Decisions

## Decision GOV-001: Policy Language
**Date:** 2024-01-17  
**Status:** Approved  
**Rationale:** Using JSON Schema with cryptographic proofs. JSON is ubiquitous, schemas are machine-verifiable, and we can embed signatures directly in policies.

## Decision GOV-002: Enforcement Triggers
**Date:** 2024-01-17  
**Status:** Approved  
**Rationale:** Four enforcement points: compile, load, runtime, update. This covers the entire lifecycle without gaps.

## Decision GOV-003: Nano-Scale Optimization
**Date:** 2024-01-17  
**Status:** Approved  
**Rationale:** Each policy limited to 1KB, entire engine under 5KB. Uses deterministic finite automata for rule matching to minimize memory.
