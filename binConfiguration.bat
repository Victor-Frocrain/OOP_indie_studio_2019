if exist Debug\bomberman.exe (
	xcopy /y bin\Irrlicht.dll Debug\
	xcopy /y bin\openal32.dll Debug\
	xcopy /y bin\sfml-audio-d-2.dll Debug\
	xcopy /y bin\sfml-system-d-2.dll Debug\
) else if exist Release\bomberman.exe (
	xcopy /y bin\Irrlicht.dll Release\
	xcopy /y bin\openal32.dll Release\
	xcopy /y bin\sfml-audio-d-2.dll Release\
	xcopy /y bin\sfml-system-d-2.dll Release\
)
exit