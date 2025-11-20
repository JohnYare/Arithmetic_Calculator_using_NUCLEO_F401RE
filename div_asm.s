            AREA |.text|, CODE, READONLY
div_asm     PROC
            EXPORT div_asm
    	    SDIV R0, R1
    	    BX LR
	        ENDP
	        ALIGN
	        END