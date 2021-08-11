-- Funcional-8puzzle

local P = {}
local P_mt = { __index = P }


local Puzzle = {
                  {  -- Goal 1
                     Goal = { {1, 2, 3}, {4, 5, 6}, {7, 8, 0} },
                     Test = {
                              { {1, 2, 3}, {4, 5, 6}, {7, 8, 0} }, -- confirma=0  "Goal" passed
                              { {7, 2, 4}, {5, 0, 6}, {8, 3, 1} }  -- confirma=16 passed
                            }
                  }
                }
               


local Linha = {}
local Coluna = {}
local Fila = {}
local Vertices = {}


function MakeIndexes(goal)
    local Linha = {}
    local Coluna = {}
    local index
    for x = 1,3 do
        for y = 1,3 do
            index = goal[x][y]
            if goal[x][y] == 0 then index = 9 end
            Linha[index] = x
            Coluna[index] = y
        end
    end
    return Linha,Coluna
end



function P:novo()
    return setmetatable( { State = {{},{},{}}, Ancestor = 0, Cost = 0 , Heuristics = 0 }, P_mt )
end



function P:print()
    for x = 1,3 do
        for y = 1,3 do
            io.write(string.format("%2i ", self.State[x][y]))
        end
        print()
    end
    print(" ")
end




function P:RecalcHeuristics()
    local r = 0
    for x = 1,3 do
        for y = 1,3 do
            if self.State[x][y] ~= 0 then
                r = r +
                    math.abs( Linha[ self.State[x][y] ] -x ) +
                    math.abs( Coluna[ self.State[x][y] ] -y )
                    -- print(self.State[x][y], x, y, r)
            end
        end
    end
    self.Heuristics = r
end




function P:Inicializa(...)
    if ... then    -- é possível usar a tabela de estados predefinida
        self.State = ...
    else
        local num
        local exist = {}
        math.randomseed(os.time())
        math.random()
        for x = 1,3 do
            for y = 1,3 do
                repeat
                    num = math.random(0, 8)
                until exist[num] == nil
                exist[num] = true      -- e.g.: { [5] = true }
                self.State[x][y] = num
            end
        end
    end
    self.Ancestor = 0                  -- 0 - vertice raiz
    self:RecalcHeuristics()
    table.insert(Vertices, self)
    table.insert(Fila, 1)
end




function P:Verifica(value)
    local confirma = 0
    for i = 1,9 do
        local x,y = Linha[i], Coluna[i]
        if self.State[x][y] == value then
            return confirma
        end
        if self.State[x][y] > value then
            confirma = confirma + 1
        end
    end
    return confirma
end




function P:ehSolucao()
    local confirma = 0
    for x = 1,3 do
        for y = 1,3 do
            if self.State[x][y] > 0 then
                confirma = confirma + self:Verifica(self.State[x][y])
            end
        end
    end
    print("confirma="..confirma)
    if (confirma % 2 == 0) then
       return true
    else
       return false
    end
end




function P_mt:__eq(v)           -- usado pelo isGoal()
    for x = 1,3 do
        for y = 1,3 do
            if self.State[x][y] ~= v.State[x][y] then
                return false
            end
        end
    end
    return true
end




function isGoal(goal,v)
    local Goal = P:novo()
    Goal.State = goal
    if Goal == v then       -- ver funcao P_mt:__eq()
        return true
    end
    return false
end




function P:copia(tov)
    for x = 1,3 do
        for y = 1,3 do
            tov.State[x][y] = self.State[x][y]
        end
    end
end




function Vizinho(v, idx)
    local zx, zy
    for x = 1,3 do
        for y = 1,3 do
            if v.State[x][y] == 0 then
                zx = x
                zy = y
                break
            end
        end
    end


    local dx = {-1,  0,  1,  0}
    local dy = { 0, -1,  0,  1}


    for k = 1,4 do
        local i = zx + dx[k]
        local j = zy + dy[k]
        if i >= 1 and j >= 1 and i <= 3 and j <= 3 then
             Vertex = P:novo()
             v:copia(Vertex)                         -- copia v.State para Vertex.State
             Vertex.State[i][j] = 0                 -- nova posicao para "0"
             Vertex.State[zx][zy] = v.State[i][j]
             Vertex.Cost = v.Cost + 1               -- Parent_vertex_cost + 1
             Vertex:RecalcHeuristics()
             Vertex.Ancestor = idx
             for i = 1,#Vertices do
                 if Vertex == Vertices[i] then
                     Vertex = nil
                     break;
                 end
             end
             if Vertex ~= nil then
                 -- 
                 table.insert(Vertices, Vertex)


                 table.insert(Fila, #Vertices)
                 table.sort(Fila, function(a,b) return Vertices[a].Heuristics+Vertices[a].Cost < Vertices[b].Heuristics+Vertices[b].Cost end)

             end
        end
    end
end




-- main


local num_puzzle = 1          -- Nº de quebra cabeças
local num_teste = 2           -- Nº de testes




local puzzle = Puzzle[num_puzzle]
local Goal = puzzle.Goal
local Test = puzzle.Test[num_teste]


Linha,Coluna = MakeIndexes(Goal)


local A = P:novo()
A:Inicializa(Test)
A:print()


if A:ehSolucao() then
    print("Solução existe");
else
    print("Sem solução");
    os.exit()
end


-- os.exit()


local v = P:novo()
local contador = 0      -- contador de iterações
local idx
while #Fila ~= 0 do
    idx = Fila[1]    -- índice do elemento atual dos vértices
    v = Vertices[idx]
    table.remove(Fila,1)
    contador = contador + 1
    if isGoal(Goal,v) then
        print("--- Fim ---")
        v:print()
        local t = v.Ancestor
        if t > 0 then
            while Vertices[t].Ancestor ~= 0 do
                Vertices[t]:print()
                t = Vertices[t].Ancestor
           end
        end
        print("Iterações = "..contador)
        break
    else
        Vizinho(v, idx)
    end
end