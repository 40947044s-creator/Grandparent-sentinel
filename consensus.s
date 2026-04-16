/* * Adelic Transition Engine - Core Surgery 
 * Input: x0 (Signal S), x1 (Prime 53)
 * Output: x0 (Inference I), x1 (Residue R)
 */
.global _snap_surgery
_snap_surgery:
    // x0 = signal (S)
    // x1 = modulus (53)
    // x2 = address of R (&R) <--- We MUST NOT overwrite this yet

    udiv    x9, x0, x1      // Use x9 for the quotient (I) to save x2
    msub    x10, x9, x1, x0 // x10 = R (S - I * 53)
    
    // THE FIX: Store the remainder (x10) into the memory address held in x2
    str     x10, [x2]       
    
    // Return the Quotient (I) in x0 as per AAPCS64
    mov     x0, x9          
    ret
