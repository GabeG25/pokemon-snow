	.align 2
voicegroup_urayne_stream::
	@ Single direct-sound voice for raw 8-bit PCM streamed playback. Plain
	@ `voice_directsound` (type 0x00) honors wav->freq directly. Triggered at
	@ key 60 (Cn3) so the engine's scale table yields wav->freq exactly.
	voice_directsound 60, 0, DirectSoundWaveData_urayne_stream, 255, 0, 255, 0
