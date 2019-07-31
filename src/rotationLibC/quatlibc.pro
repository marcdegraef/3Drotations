Pro quatlibc
; initiation routine for the quaternion library.  Not necessary if these functions are in your path.  


path = FILE_DIRNAME(ROUTINE_FILEPATH())

cd, current = currentpath

cd, path


files = FILE_SEARCH( 'quat*.pro')

files = files[where(files NE 'quatlib.pro', count)]

If count GT 0 THEN BEGIN
  files = strsplit(files, '.pro', /extract, /regex)
  Foreach file, files Do $
    RESOLVE_ROUTINE, file, /compile_full, /either, /no_recompile
ENDIF
cd, currentpath

end