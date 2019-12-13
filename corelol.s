                 				




.comment	"aff, just kidding"

.name 		"laugh"  


hello:						


	sti		r1, %:alive, %1     



				fork	%:alive
	add		r2, r3, r4



alive:
	live	%0
	zjmp	%:alive
