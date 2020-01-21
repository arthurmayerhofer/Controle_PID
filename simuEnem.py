linguagens = 576.4
natureza = 557.6
humanas = 639
matematica = 732.5
redacao = 940

curso = input('Digite o curso e lugar:')

ling_peso = input('Digite o peso de linguagens:')
natu_peso = input('Digite o peso de natureza:')
hum_peso = input('Digite o peso de humanas:')
mate_peso = input('Digite o peso de matematica:')
red_peso = input('Digite o peso de redacao:')

soma_pesos = float(ling_peso) + float(natu_peso) + float(hum_peso) + float(mate_peso) + float(red_peso)

calc = ((linguagens*float(ling_peso)) + (natureza*float(natu_peso)) + (humanas*float(hum_peso)) + (matematica*float(mate_peso)) + (redacao*float(red_peso))) / soma_pesos

nota = ('nota de', curso, ':', str(calc))
print(nota)


