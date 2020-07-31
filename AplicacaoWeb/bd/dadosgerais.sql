-- phpMyAdmin SQL Dump
-- version 4.9.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Tempo de geração: 31-Jul-2020 às 20:19
-- Versão do servidor: 8.0.18
-- versão do PHP: 7.3.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Banco de dados: `geodados`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `dadosgerais`
--

CREATE TABLE `dadosgerais` (
  `id` int(11) NOT NULL,
  `latitude` float NOT NULL,
  `longitude` float NOT NULL,
  `data` date NOT NULL,
  `hora` time NOT NULL,
  `temperatura` float NOT NULL,
  `pluviometro` varchar(20) COLLATE utf8mb4_general_ci NOT NULL,
  `UmidadeAr` varchar(20) COLLATE utf8mb4_general_ci NOT NULL,
  `Anemometro` varchar(20) COLLATE utf8mb4_general_ci NOT NULL,
  `Luminosidade` varchar(20) COLLATE utf8mb4_general_ci NOT NULL,
  `RadiacaoSol` varchar(20) COLLATE utf8mb4_general_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;


--
-- Índices para tabela `dadosgerais`
--
ALTER TABLE `dadosgerais`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT de tabela `dadosgerais`
--
ALTER TABLE `dadosgerais`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
