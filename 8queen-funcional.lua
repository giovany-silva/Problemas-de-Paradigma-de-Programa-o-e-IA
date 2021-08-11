-- Funcional-8queen

tamanho = 8 -- tamanho do tabuleiro

-- verifica se a posição (n, c) não sofre ataque
function verifica (a, n ,c)
    for i = 1, n - 1 do -- para cada rainha já alocada
        if (a[i] == c) or           -- mesma coluna
        (a[i] - i == c - n) or      -- mesma diagonal
        (a[i] + i == c + n) then    -- mesma diagonal
            return false -- se for atacado retorna falso
        end
    end
    return true -- se não for atacado retorna true
end

-- imprime a solução
function imprime (a)
    for i = 1, tamanho do             -- para cada linha
        for j = 1, tamanho do        -- para cada coluna
            -- escreve Q onde as rainhas vão ficar 
            io.write(a[i] == j and "Q" or "-", " ")
        end
        io.write("\n")
    end
    io.write("\n")
end

-- add no tabuleiro 'a' todas as rainhas de  'n' até o 'tamanho'
function adiciona (a, n)
    if n > tamanho then -- verifica se todas as rainhas já foram alocadas
        imprime(a)
    else -- coloca a enésima rainha
        for c = 1, tamanho do
            if verifica(a, n, c) then
                a[n] = c -- coloque a enésima rainha na coluna 'c'
                adiciona(a, n + 1)
            end
        end
    end
end

-- roda o programa
adiciona({}, 1)
