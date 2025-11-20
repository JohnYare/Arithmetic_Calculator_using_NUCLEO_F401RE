            AREA |.text|, CODE, READONLY
sub_asm     PROC
            EXPORT sub_asm
            SUB R0, R1
            BX LR
            ENDP
            ALIGN
            END