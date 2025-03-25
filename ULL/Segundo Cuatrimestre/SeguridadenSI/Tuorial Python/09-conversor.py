
num = int(input("Ingrese temperatura a convertir: "))
type(num)
eleccion = input("Es Fahrenhei(F) o Celsius(C)?: ")
if str(eleccion) == "F":
    print((num - 32) * 5/9)
elif str(eleccion) == "C":
    print((num * 9/5) + 32)
else:
    print("Escala incorrecta")