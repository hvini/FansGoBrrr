# 🧠 ANN from Scratch in C (CPU → GPU)

## 🚧 Phase 1: CPU Implementation

- [ ] 🔧 **Build System** – Set up Makefile or CMake
- [ ] 🧱 **Data Structures** – Define `Matrix`, `Layer`, `Network`
- [ ] ➗ **Matrix Operations** – Add, multiply, transpose
- [ ] 🔁 **Activation Functions** – Sigmoid, ReLU, Softmax
- [ ] 🔄 **Forward Propagation** – Weighted sums + activations
- [ ] 📉 **Loss Function** – MSE or Cross-Entropy
- [ ] 🧮 **Backpropagation** – Calculate gradients
- [ ] 🏋️ **Weight Updates** – Apply SGD
- [ ] 🌀 **Training Loop** – Run for N epochs
- [ ] ✅ **Test Cases (CPU)**
  - Matrix operations match expected results
  - Activation outputs correct for sample inputs
  - Forward propagation output sanity check
  - Backpropagation gradients validated numerically
  - Training on XOR dataset: loss decreases, correct outputs

---

## 🚀 Phase 2: GPU Acceleration (CUDA)

- [ ] ⚙️ **CUDA Setup** – Configure build and test kernel
- [ ] 🧊 **Matrix Ops (GPU)** – Port add, multiply, etc.
- [ ] 🌐 **Activations (GPU)** – Parallel element-wise ops
- [ ] 🧬 **Forward Prop (GPU)** – Matrix ops + activations
- [ ] 🔙 **Backprop (GPU)** – Gradient calculation on GPU
- [ ] 🏁 **Training Loop (GPU)** – Fully GPU-accelerated
- [ ] 🔍 **Test Cases (GPU)**
  - GPU matrix ops produce identical results to CPU
  - Activation functions match CPU outputs
  - Forward propagation matches CPU outputs
  - Backpropagation gradients match CPU calculations
  - Training on XOR dataset converges with GPU
     
---
