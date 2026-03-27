Minimum **6 entries** required.  
Each entry documents learning and reasoning. Fabricated bugs are not expected.

---

## Allowed Entry Types
Each entry may be one of the following:

1) **Bug Fix Entry**
- The issue encountered.
- Error messages or symptoms.
- Attempts made.
- Final resolution.

2) **Edge Case / Testing Entry**
- A failure discovered through testing.
- The specific input/state that caused it.
- The change you made to handle it correctly.

3) **Engineering Decision Entry (up to 2 allowed)**
- A design decision you made.
- An alternative approach you considered.
- Why you chose one approach over another (tradeoffs).

---

### Entry 1
**Date:** 2026-03-18  
**Entry Type:** Engineering Decision  
**Task worked on:** Project structure + division rule + ambiguous single-number input handling  
**Issue or decision:** The assignment allows either integer or double division, and expressions like `42` could be interpreted as both infix and postfix. I wanted consistent rules for grading and predictable behavior.  
**Error message / symptom (if applicable):** N/A  
**What I tried:** I reviewed the requirements and compared the consequences of integer vs double division and how to classify single-token inputs.  
**Fix / resolution (or final decision):** I chose double division (store numeric values as `double` and use `/` directly) to avoid surprising integer truncation. For input with a single number token, I treat it as POSTFIX because my program checks postfix validity first, this is more consistent and also documented.  
**Commit(s):** `implement ArrayStack push/pop/top/empty/size with safe empty handling`

---

### Entry 2
**Date:** 2026-03-18   
**Entry Type:** Bug Fix Entry  
**Task worked on:** `ArrayStack<T>` implementation and empty-stack safety  
**Issue or decision:** `pop()` and `top()` must be handled safely when the stack is empty. I needed a consistent behavior that prevents any undefined results or future tech debt.  
**Error message / symptom (if applicable):** Without checks, calling `top()` on an empty vector caused undefined behavior and crash risk.  
**What I tried:** I tested pushing/popping values and intentionally called `top()` and `pop()` on an empty stack to confirm what happens.  
**Fix / resolution (or final decision):** I implemented `ArrayStack<T>` using `std::vector<T> data`. I added empty checks and chose to throw `std::out_of_range` for both `top()` and `pop()` when empty. This keeps everything more consistent and makes errors easier to detect during my testing.  
**Commit(s):** `implement ArrayStack push/pop/top/empty/size with safe empty handling`

---

### Entry 3
**Date:** 2026-03-19  
**Entry Type:** Bug Fix Entry  
**Task worked on:** Tokenizer (`tokenize`) for numbers/operators/parentheses  
**Issue or decision:** Expressions can be typed with or without spaces (ex: `3+4*2` vs `3 + 4 * 2`). Tokenization must correctly split numbers and single character operators/parentheses, and reject invalid characters.  
**Error message / symptom (if applicable):** Initial tokenization attempts treated `3+4` as one token or failed to detect operators when there were no spaces.  
**What I tried:** I tested multiple inputs:
- `3+4*2`
- `(3+4)*2`
- `3 4 2 * +`
- `3 + @ 4`  
  and printed tokens to verify correct parsing.  
 
**Fix / resolution (or final decision):** I updated tokenize to scan left to right, making sure to skip any whitespace, grouping consecutive numbers into one number token, and treating `+ - * / ( )` as single character tokens. If any other character appears, mark the expression invalid for detection.  
  **Commit(s):** `implement tokenizer for numbers/operators/parentheses`

---

### Entry 4
**Date:** 2026-03-23  
**Entry Type:** Edge Case / Testing Entry  
**Task worked on:** Postfix validation (`isValidPostfix`) + postfix evaluation (`evalPostfix`)  
**Issue or decision:** Postfix needs validation before evaluation. Invalid postfix expressions should be classified as NEITHER, not partially evaluated.  
**Error message / symptom (if applicable):** Expressions like `3 +` or `3 4 + +` cause stack underflow during evaluation if not validated first.  
**What I tried:** I tested postfix validation using simulated stack depth rules on:
- valid: `3 4 +`, `3 4 2 * +`
- invalid: `3 +`, `3 4 + +`, `+ 3 4`, `3 4 ) +`

Then I double-checked evaluation only runs after validation is successful.  
**Fix / resolution (or final decision):** I implemented postfix validity using a depth counter: numbers increase depth, operators require depth ≥ 2 and reduce depth by 1. Parentheses immediately invalidate postfix. A postfix expression is valid only if final depth is exactly 1. Evaluation uses `ArrayStack<double>` and pops two operands for each operator. I also added extra stack-size checks to prevent any crashes.  
**Commit(s):** `implement isValidPostfix using stack depth rules`, `implement evalPostfix using ArrayStack<double>`

---

### Entry 5
**Date:** 2026-03-27  
**Entry Type:** Bug Fix Entry  
**Task worked on:** Converting infix to postfix (`infixToPostfix`) using the Shunting-Yard idea  
**Issue or decision:** I had to make sure my infix-to-postfix conversion handled operator precedence correctly (* and / before + and -) and also handled left-to-right order for operators with the same precedence (left-associative). The tricky part was deciding when to pop operators off the stack.  
**Error message / symptom (if applicable):** My first version sometimes gave the wrong postfix order. That caused wrong final answers for some expressions. For example, `3 - 2 - 1` could accidentally act like `3 - (2 - 1)` instead of the correct `(3 - 2) - 1`.  
**What I tried:** I tested a few expressions where precedence/order matters:
- `3 + 4 * 2` should become `3 4 2 * +`
- `(3 + 4) * 2` should become `3 4 + 2 *`
- `3 - 2 - 1` should become `3 2 - 1 -` (because subtraction goes left-to-right)  
  I printed out the postfix tokens to compare them with what I expected.  

**Fix / resolution (or final decision):** I fixed my popping logic so that when I see a new operator, I keep popping from the operator stack while the top operator has higher OR equal precedence. I used `>=` (not just `>`) because all operators are left-associative in this assignment. That made the postfix output and final evaluation match expected results.  
**Commit(s):** `implement infixToPostfix (Shunting Yard) using ArrayStack<Token>`

---
