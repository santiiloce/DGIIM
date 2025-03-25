lenguajes = ["Python", "Ruby", "PHP", "C++"]
print(lenguajes[1])
lenguajes[1] = "Java"
# Con los inidces negativos accedo a los elementos por el final
lenguajes[-1] = "JavaScript"
# Los : indican un rango de elementos
print(lenguajes[1:3])
#Imprimir desde el inicio hasta i
print(lenguajes[:3])
#Imprimir hasta el final desde i
print(lenguajes[2:])