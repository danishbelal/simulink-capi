# Lese die LICENSE Datei und präfixiere jede Zeile
# mit "// ".
#
# Damit kann die präfixierte Datei direkt in C++ Quellen
# kopiert werden.
with open("license-header", "r") as input, open("LICENSE-commented", "w") as output:
    for line in input:
        output.write("// " + line)