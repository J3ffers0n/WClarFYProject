<!DOCTYPE html>
<html lang="pt-br">
    
    <head>
        <meta charset="utf-8" />
        <title>clariFY</title>
        <link rel="stylesheet" type="text/css" href="css/estilo.css">
    </head>
 
    <body>

        <?php
        
            // Incluindo o arquivo de conexão com MySQL
            include 'api/conexao.php';
            //include 'api/dht11.php';
            
            // Podemos criar um log de ações para vários registros.
            $arquivo = fopen("logs/log.txt","w");

            // Selecionando todos os dados da tabela 'dadosgerais'.
            $sql = "SELECT * FROM dadosgerais";

            $consulta = $pdo->query($sql);

            if ( $consulta->rowCount() > 0 ){

                $dadosJson = "[";

                $i = 0;

                while ($linha = $consulta->fetch(PDO::FETCH_ASSOC)) {

                    $dadosJson .= "{";
                    
                    $dadosJson .= "\"Id\": "             . $linha['id']                   . ",";
                    $dadosJson .= "\"Latitude\": "       . (float)$linha['latitude']      . ",";
                    $dadosJson .= "\"Longitude\": "      . (float)$linha['longitude']     . ",";
                    //$dadosJson .= "\" :\"" . (string)$linha['data'] . ",";
                    //$str .= "\":\"" . (string)$linha['hora'] . ",";
                    $dadosJson .= "\"Temperatura\": "    . (float)$linha['temperatura']   . ",";
                    $dadosJson .= "\"pluviometro\": \""  . (string)$linha['pluviometro']  . "\",";
                    $dadosJson .= "\"UmidadeAr\": \""    . (string)$linha['UmidadeAr']    . "\",";
                    $dadosJson .= "\"Anemometro\": \""   . (string)$linha['Anemometro']   . "\",";
                    $dadosJson .= "\"Luminosidade\": \"" . (string)$linha['Luminosidade'] . "\",";
                    $dadosJson .= "\"RadiacaoSol\": \""  . (string)$linha['RadiacaoSol']  . "\"";
                    
                    $dadosJson .= $i < ($consulta->rowCount()-1) ? "}," : "}";
                    $i++;

                }

            }else{

                fwrite($arquivo,"Não há registros no MySQL");

            }

            $dadosJson .= "]";

            fclose($arquivo);

            // Cria o arquivo 'dadosFechados.json'.
            $arquivo = fopen("js/dadosFechados.json", "w");
            
            // Escreve o conteúdo Json no arquivo.
            fwrite($arquivo, $dadosJson);
            
        ?>

    	<div id="mapa" style="height: 500px; width: 600px"></div>
		
		<script src="js/jquery.min.js"></script>
 
        <!-- Google Maps API Javascript -->
        <script src="http://maps.googleapis.com/maps/api/js?key=AIzaSyCrOA_XSChxlRBp-5BTM7mGjopLmwEwDpA&sensor=false"></script>
        
        <!-- Caixa com a estrutura das informações -->
        <script src="js/popup.js"></script>
		
        <!-- Agrupando os marcadores no mapa -->
		<script src="js/agrupamento.js"></script>
 
        <!-- Arquivo de inicialização do mapa -->
        <script src="js/mapa.js"></script>
        
    </body>

</html>