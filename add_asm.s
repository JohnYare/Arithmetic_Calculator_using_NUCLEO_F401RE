            AREA |.text|, CODE, READONLY
add_asm     PROC
            EXPORT add_asm
            ADD R0, R1
            BX LR
            ENDP
            ALIGN
            END