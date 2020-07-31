<?php
	
	$servidor     = "localhost";
    $bancodedados = "geodados";
    $usuariobd    = "root";
    $senhabd      = "mysql";
    
    $sql = "mysql:host=$servidor;dbname=$bancodedados;";
    
    try { 
        $pdo = new PDO($sql, $usuariobd, $senhabd);
        // Gravar um log de sucesso.
    } catch (PDOException $e) {
        // Gravar um log de erro.
    }
	
	date_default_timezone_set('America/Sao_Paulo');
	
?>