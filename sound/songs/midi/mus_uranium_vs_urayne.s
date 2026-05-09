	.include "MPlayDef.s"

	@ Streamed PCM (DPCM) playback of the actual Pokemon Uranium Urayne battle
	@ theme. mid2agb is bypassed; this song asm is hand-written. The voicegroup
	@ holds one voice_directsound_comp pointing at the encoded sample whose
	@ header carries loop_start/loop_end, so triggering one tied note plays the
	@ full track and loops automatically inside the m4a sample mixer.

	.equ	mus_uranium_vs_urayne_grp, voicegroup_urayne_stream
	.equ	mus_uranium_vs_urayne_pri, 0
	.equ	mus_uranium_vs_urayne_rev, reverb_set+0
	.equ	mus_uranium_vs_urayne_mvl, 127
	.equ	mus_uranium_vs_urayne_key, 0
	.equ	mus_uranium_vs_urayne_tbs, 1
	.equ	mus_uranium_vs_urayne_exg, 0
	.equ	mus_uranium_vs_urayne_cmp, 1

	.section .rodata
	.global	mus_uranium_vs_urayne
	.align	2

mus_uranium_vs_urayne_1:
	.byte	KEYSH, mus_uranium_vs_urayne_key+0
	.byte	TEMPO, 75
	.byte	VOICE, 0
	.byte	PAN, c_v+0
	.byte	VOL, 127*mus_uranium_vs_urayne_mvl/mxv
	.byte	TIE, Cn3, v127
mus_uranium_vs_urayne_1_wait:
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	W96
	.byte	GOTO
	 .word	mus_uranium_vs_urayne_1_wait

	.align	2
	.global	mus_uranium_vs_urayne
mus_uranium_vs_urayne:
	.byte	1, 0	@ trackCount, blockCount
	.byte	mus_uranium_vs_urayne_pri, mus_uranium_vs_urayne_rev
	.word	mus_uranium_vs_urayne_grp
	.word	mus_uranium_vs_urayne_1
