#ifndef TRACE_H
#define TRACE_H
#include <string>
#include <vector>
#include <optional>
#include <iostream>

enum OperationType {
    STORE,
    LOAD,
    COMPUTE,
    OTHER
};

enum ComputeType {
    ADD,
    SUB,
    AND,
    OR,
    XOR,
    SLL,
    SRL,
    SRA,
    SLT,
    SLTU,
    INVALID
};

inline ComputeType stocompute_type(const std::string& str) {
    if (str == "add") return ComputeType::ADD;
    else if (str == "sub") return ComputeType::SUB;
    else if (str == "and") return ComputeType::AND;
    else if (str == "or") return ComputeType::OR;
    else if (str == "xor") return ComputeType::XOR;
    else if (str == "sll") return ComputeType::SLL;
    else if (str == "srl") return ComputeType::SRL;
    else if (str == "sra") return ComputeType::SRA;
    else if (str == "slt") return ComputeType::SLT;
    else if (str == "sltu") return ComputeType::SLTU;
    else return ComputeType::INVALID;
}

struct Operation {
    int core;                           // core id (must)
    OperationType operation;            // (must)
    std::vector<std::string> rs;        // rs1 for load and store, rs1 and rs2 for compute (must)
    std::optional<uint32_t> address;    // Just for load and store (optional)
    std::optional<std::string> result;  // rd for compute and store (optional)
    std::optional<ComputeType> compute_type; // Just for compute (optional)
};

inline void dbg_operation(const Operation& op) {
    std::cout << "core: " << op.core << ", operation: ";
    switch (op.operation) {
        case STORE: std::cout << "store"; break;
        case LOAD: std::cout << "load"; break;
        case COMPUTE: std::cout << "compute"; break;
        default: std::cout << "other"; break;
    }
    std::cout << ", rs: ";
    for (const auto& r : op.rs) {
        std::cout << r << " ";
    }
    if (op.address) {
        std::cout << ", address: 0x" << std::hex << *op.address;
    }
    if (op.result) {
        std::cout << ", result: " << *op.result;
    }
    if (op.compute_type) {
        std::cout << ", compute_type: " << *op.compute_type;
    }
    std::cout << std::endl;
}

// std::vector<Operation> operations = {
//     {1, OperationType::STORE, "a0", 0x2000, std::nullopt, std::nullopt},
//     {0, OperationType::LOAD, "a1", 0x2000, std::nullopt, std::nullopt},
//     {1, OperationType::LOAD, "a1", 0x1000, std::nullopt, std::nullopt},
//     {0, OperationType::COMPUTE, std::nullopt, std::nullopt, "a1 a0", "a0"}
// };

#endif // TRACE_H