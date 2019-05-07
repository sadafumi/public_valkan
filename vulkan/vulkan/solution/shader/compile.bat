for %%q in (%*) do (glslangValidator.exe -V %%q -l -o %%q.spv)
pause