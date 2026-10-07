# 01 · Complexity Analysis
Run everything: `./dsa test 01` · Status: `./dsa list 01`

This topic has no code exercises: `./dsa test 01` reports that there is nothing to run. The work is the pen-and-paper worksheet.

## Diagnostic
Answer questions 1 and 5 of WORKSHEET.md without notes. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Big-O, Big-Ω, and Big-Θ, and the distinction between worst-case, average-case, and amortized bounds.
- [ ] The common growth classes and their practical input-size limits (approximately 10⁸ simple operations per second).
- [ ] Amortized analysis, using dynamic array doubling as the canonical example.
- [ ] Recurrence relations and the Master Theorem.
- [ ] Space complexity, including recursion stack depth.

## Implement
- [ ] Complete WORKSHEET.md; check against `solutions/01_complexity/ANSWERS.md` only after finishing. (Derive by hand the complexity of merge sort, binary search, building a heap, and recursive Fibonacci with and without memoization.)

## Practice
- [ ] For each problem solved in later topics, write the time and space complexity before running the code.

## CLRS quick reference (≈45 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Notation feels shaky | Ch. 3 (3e) / Ch. 3 (4e), "Growth of Functions" / "Characterizing Running Times" | Definitions of O, Ω, Θ only (≈15 min) | You can state the O/Ω/Θ definitions cold. |
| Q5 | §4.5 (3e) / §4.5 (4e), "The master method for solving recurrences" | Theorem statement and the worked examples. 4e: note the extended case 2 (≈15 min) | You can apply all three cases and say when none applies. |
| Q6 | §17.4 (3e) / §16.4 (4e), "Dynamic tables" | Table expansion only, skip contraction (≈15 min) | You can show doubling gives O(1) amortized append. |

## Mastery criteria
- [ ] The complexity of any solution can be stated and justified without hesitation.
- [ ] The Master Theorem can be applied to standard divide-and-conquer recurrences.
