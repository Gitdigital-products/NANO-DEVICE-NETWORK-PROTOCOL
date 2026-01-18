COMPILE-TIME ENFORCEMENT HOOKS/TEST SUITE/File: tests/test_governance.c
  #include "governance_engine.h"
#include <assert.h>

void test_policy_loading() {
    governance_engine engine;
    governance_init(&engine);
    
    nano_policy test_policy = {
        .policy_id = "GOV-SEC-TEST01",
        .rule_count = 1
    };
    strcpy(test_policy.rules[0].condition, "total_memory > 100");
    test_policy.rules[0].action = 1; // DENY
    
    assert(load_policy(&engine, &test_policy) == 1);
    assert(engine.policy_count == 2); // Default + new
}

void test_enforcement_decision() {
    governance_engine engine;
    governance_init(&engine);
    
    system_state state = {
        .total_memory = 5000, // Exceeds limit
        .crypto_algorithm = 1, // kyber512 (good)
        .dependency_count = 0
    };
    
    uint8_t result = governance_enforce(&engine, "test", &state);
    assert(result == 1); // Should be DENY due to memory
}

void test_decision_logging() {
    governance_engine engine;
    governance_init(&engine);
    
    system_state state = {.total_memory = 5000};
    governance_enforce(&engine, "test", &state);
    
    assert(engine.log_index == 1); // One decision logged
    assert(engine.log[0].action_taken == 1); // DENY action
}
