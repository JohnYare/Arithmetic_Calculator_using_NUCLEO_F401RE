            AREA |.text|, CODE, READONLY
mul_asm     PROC
    	    EXPORT mul_asm
    	    MUL R0, R1
    	    BX LR
	        ENDP
	        ALIGN
	        END