# Lese die LICENSE Datei und präfixiere jede Zeile
# mit "// ".
#
# Damit kann die präfixierte Datei direkt in C++ Quellen
# kopiert werden.
with open("license-header", "r") as in_file, open("LICENSE-commented", "w") as out_file:
    for line in in_file:
        out_file.write("// " + line)
