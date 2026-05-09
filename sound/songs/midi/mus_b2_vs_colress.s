	.include "MPlayDef.s"

	@ Streamed PCM playback. mid2agb is bypassed; this song asm is hand-written.
	@ The voicegroup carries one direct_sound_no_resample voice; the .bin sample
	@ has loop_start/loop_end set in its header, so triggering one tied note plays
	@ the audio and loops automatically inside the m4a sample mixer.

	.equ	mus_b2_vs_colress_grp, voicegroup_colress_stream
	.equ	mus_b2_vs_colress_pri, 0
	.equ	mus_b2_vs_colress_rev, reverb_set+0
	.equ	mus_b2_vs_colress_mvl, 127
	.equ	mus_b2_vs_colress_key, 0
	.equ	mus_b2_vs_colress_tbs, 1
	.equ	mus_b2_vs_colress_exg, 0
	.equ	mus_b2_vs_colress_cmp, 1

	.section .rodata
	.global	mus_b2_vs_colress
	.align	2

mus_b2_vs_colress_1:
	.byte	KEYSH, mus_b2_vs_colress_key+0
	.byte	TEMPO, 75
	.byte	VOICE, 0
	.byte	PAN, c_v+0
	.byte	VOL, 127*mus_b2_vs_colress_mvl/mxv
	.byte	TIE, Cn3, v127
mus_b2_vs_colress_1_wait:
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	GOTO
	 .word	mus_b2_vs_colress_1_wait

	.align	2
	.global	mus_b2_vs_colress
mus_b2_vs_colress:
	.byte	1, 0	@ trackCount, blockCount
	.byte	mus_b2_vs_colress_pri, mus_b2_vs_colress_rev
	.word	mus_b2_vs_colress_grp
	.word	mus_b2_vs_colress_1
