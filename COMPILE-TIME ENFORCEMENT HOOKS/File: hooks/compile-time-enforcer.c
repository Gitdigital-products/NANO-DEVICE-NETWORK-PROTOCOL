COMPILE-TIME ENFORCEMENT HOOKS/File: hooks/compile-time-enforcer.c
  /*
Compile-Time Governance Enforcement
Runs during build process to prevent policy violations
*/

#include <stdio.h>
#include <string.h>

// Check source code for violations
int check_source_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    
    char line[256];
    int violations = 0;
    
    while (fgets(line, sizeof(line), f)) {
        // Check for banned functions (non-quantum-safe)
        const char *banned[] = {"rand()", "srand()", "malloc", "time(", "sleep("};
        for (int i = 0; i < 5; i++) {
            if (strstr(line, banned[i])) {
                printf("❌ Governance Violation: %s in %s\n", banned[i], filename);
                violations++;
            }
        }
        
        // Check for large buffers (>256 bytes)
        if (strstr(line, "[256]") || strstr(line, "[512]")) {
            printf("⚠️ Warning: Large buffer in %s - exceeds nano scale\n", filename);
        }
        
        // Check for external includes
        if (strstr(line, "#include <") && 
            !strstr(line, "quantum_safe.h") && 
            !strstr(line, "governance_engine.h")) {
            printf("⚠️ Warning: External dependency in %s\n", filename);
        }
    }
    
    fclose(f);
    return violations;
}

// Main compile-time enforcement
int main(int argc, char *argv[]) {
    printf("🔐 GitDigital Compile-Time Governance Enforcer\n");
    
    int total_violations = 0;
    for (int i = 1; i < argc; i++) {
        total_violations += check_source_file(argv[i]);
    }
    
    if (total_violations > 0) {
        printf("\n❌ Build failed: %d governance violations\n", total_violations);
        return 1;
    }
    
    printf("\n✅ All governance checks passed\n");
    return 0;
}
