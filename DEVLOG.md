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

