# Prime Detector (C Implementation)

A lightweight, highly optimized command-line utility for primality testing, written in C. This tool utilizes the $6k \pm 1$ optimization method to perform efficient trial division, making it a suitable educational tool and a performant utility for quick checks on standard integer types.

## 🧮 The Algorithm: $6k \pm 1$ Optimization

Naive trial division checks every odd number up to $\sqrt{N}$. This implementation improves upon that by observing the properties of integers modulo 6.

All integers $n \ge 5$ can be expressed in the form $6k + i$, where $k$ is a non-negative integer and $i \in \{0, 1, 2, 3, 4, 5\}$.

* **$6k + 0, 6k + 2, 6k + 4$**: These are divisible by 2.
* **$6k + 3$**: This is divisible by 3.

Consequently, all prime numbers greater than 3 must take the form of either:
$$6k + 1 \quad \text{or} \quad 6k + 5 \quad (\equiv 6k - 1)$$

### Performance Implication
By implementing this logic, the algorithm skips multiples of 2 and 3 automatically. Instead of incrementing by 2 (checking all odd numbers), the loop increments by 6, checking only two candidates ($i$ and $i+2$) per iteration. This reduces the number of necessary test operations by approximately **33%** compared to standard trial division.
