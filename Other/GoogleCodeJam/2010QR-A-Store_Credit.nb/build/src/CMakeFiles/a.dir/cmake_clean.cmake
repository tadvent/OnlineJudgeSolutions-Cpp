FILE(REMOVE_RECURSE
  "CMakeFiles/a.dir/main.cpp.obj"
  "a.pdb"
  "a.exe"
  "a.exe.manifest"
  "liba.dll.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/a.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
