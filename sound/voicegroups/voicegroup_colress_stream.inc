	.align 2
voicegroup_colress_stream::
	@ Single direct-sound voice for raw 8-bit PCM streamed playback. Plain
	@ `voice_directsound` (type 0x00) honors wav->freq directly; triggered at key
	@ 60 (Cn3) so the scale table yields wav->freq exactly (no resampling math).
	voice_directsound 60, 0, DirectSoundWaveData_colress_stream, 255, 0, 255, 0
