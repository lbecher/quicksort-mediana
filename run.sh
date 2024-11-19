#!/bin/bash

# Compilar o arquivo main.c
gcc main.c -o main
if [ $? -ne 0 ]; then
  echo "Erro ao compilar main.c."
  exit 1
fi

echo "Compilação bem-sucedida. Gerando arquivos CSV para subdiretórios..."

# Encontrar e processar cada arquivo .txt nos subdiretórios
find ./ -type f -name "*.txt" | while read -r file; do
  # Obter o diretório do arquivo
  dir=$(dirname "$file")
  
  # Garantir que o arquivo CSV esteja no mesmo subdiretório
  csv_file="$dir/resultados.csv"
  
  # Criar o cabeçalho do CSV se não existir
  if [ ! -f "$csv_file" ]; then
    echo "count,tempo_execucao" > "$csv_file"
  fi

  # Imprimir o arquivo que está sendo processado
  echo "Processando: $file"

  # Executar ./main e capturar a saída
  output=$(./main "$file")
  
  # Adicionar a saída ao CSV
  echo "$output" >> "$csv_file"
done

echo "Execução concluída. Arquivos CSV gerados para cada subdiretório."
