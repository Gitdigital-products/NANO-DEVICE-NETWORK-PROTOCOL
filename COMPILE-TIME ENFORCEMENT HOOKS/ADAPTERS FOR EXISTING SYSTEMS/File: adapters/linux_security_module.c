COMPILE-TIME ENFORCEMENT HOOKS/ADAPTERS FOR EXISTING SYSTEMS/File: adapters/linux_security_module.c
/*
Adapter: Linux Security Module (LSM)
Integrates governance engine into Linux kernel
*/

#include <linux/security.h>
#include <linux/module.h>
#include "governance_engine.h"

static governance_engine gitdigital_engine;

// Hook into Linux security operations
static int gitdigital_file_permission(struct file *file, int mask) {
    system_state state;
    monitor_system_state(&state);
    
    // Add file-specific context
    state.file_path = file->f_path.dentry->d_name.name;
    state.access_mask = mask;
    
    uint8_t result = governance_enforce(&gitdigital_engine, "file_access", &state);
    
    if (result == 1) return -EPERM; // Deny
    if (result == 2) return -EACCES; // Quarantine
    return 0; // Allow
}

static int gitdigital_module_load(const char *name, void *module) {
    system_state state;
    monitor_system_state(&state);
    
    state.module_name = name;
    
    uint8_t result = governance_enforce(&gitdigital_engine, "module_load", &state);
    
    if (result == 1) return -EPERM; // Deny loading
    return 0;
}

// Register with kernel
static struct security_operations gitdigital_ops = {
    .name = "gitdigital",
    .file_permission = gitdigital_file_permission,
    .kernel_module_request = gitdigital_module_load,
};

static __init int gitdigital_init(void) {
    governance_init(&gitdigital_engine);
    return register_security(&gitdigital_ops);
}
