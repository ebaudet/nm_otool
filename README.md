# NM / OTOOL


## NM :
diff whith :
$ make && ddiff ./ft_nm nm /usr/lib/libXSEvent.dylib
=> n'affiche pas le nom de la lib nromalement.
$ make && ddiff ./ft_nm nm /usr/lib/libxcselect.dylib
=> n'affiche pas le nom de la lib nromalement.
$ make && ddiff ./ft_nm nm /usr/lib/libc++.dylib
=> I (indirect symbol)
ex error :
	 0000000000011248 T __ZNKSt16nested_exception14rethrow_nestedEv
	 00000000000499c4 T __ZNKSt18bad_variant_access4whatEv
	 00000000000496c4 T __ZNKSt19bad_optional_access4whatEv
	                  U __ZNKSt20bad_array_new_length4whatEv
	-000000000000021d I __ZNKSt20bad_array_new_length4whatEv
	+                 I __ZNKSt20bad_array_new_length4whatEv (indirect for __ZNKSt20bad_array_new_length4whatEv)
-> ne pas afficher l'adresse, mais le texte suivant : " (indirect for %name%)"
