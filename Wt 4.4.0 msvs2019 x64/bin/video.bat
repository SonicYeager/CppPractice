REM This-is-a-wt-example
set PATH=%~p0;%PATH%
set OLDPWD=%CD%
REM Required until all examples accept a "--approot path" parameter
cd ..\lib\Wt\examples\feature/video

"%~p0\video.wt" --docroot .  --http-port 8080 --http-address 0.0.0.0 --resources-dir ..\..\..\share\Wt\resources %*
