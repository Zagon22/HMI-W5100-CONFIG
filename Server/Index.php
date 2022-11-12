<?PHP
	/* Obtención del dato aportado por la placa Arduino (cliente web) */
	if(isset($_GET['ledstat']))
	{
	    $ledstat = $_GET['ledstat'];
	}

	/* Declaración de variables */
	$server = "www.server.com" // Modifíquelo por el DNS de su servidor remoto o bien por su dirección IPV4.
	$user = "usuario_nombre" // Modifíquelo por el nombre del usuario con el que haya creado la base de datos.
	$pass = "usuario_contraseña" // Modifíquelo por la contraseña correspondiente al usuario anterior.
	$dbname = "base_datos_nombre" // Modífiquelo por el nombre de la base de datos.

	$enlace = mysqli_connect($server, $user, $pass, $dbname) // Establecimiento de la conexión con la base de datos.
	or die('No se puede conectar: '. mysqli_connect_error()); // Información de error ante un fallo en el intento de conexión.
	echo 'Conexión Exitosa. <BR />'; // Mensaje impreso al establecerse la conexión.
	echo '<HR />'; // Inserción de un separador.

	$consulta = mysqli_query($enlace, "INSERT INTO ledstatus(ledstat) VALUES ('$ledstat')"); // Inserción de los datos ingresados desde el cliente en la tabla indicada de la base de datos.

	/* Bifurcación del flujo del programa según la tarea anterior */
	if(!$consulta) 
	{
		echo "Error al guardar. <BR />"; // Mensaje impreso en caso de no efectuarse la instrucción sql "INSERT".
	}
	else 
	{
		echo "Datos Guardados. <BR />"; // Mensaje impreso en caso de haberse efectuado la instrucción sql "INSERT".
	}

	echo "<HR />"; // Inserción de un separador.
	echo "Registro de la base de datos: <BR />";
	echo "<HR />"; // Inserción de un separador.

	/* Confección de una tabla */
	echo "<TABLE BORDER=1 id='tabla'> 
		<TR>
		<TD> ID </TD>
		<TD> Voltaje </TD>
		</TR>";
	$sql = "SELECT * FROM ledstatus"; // Selección de todas las entradas de la tabla indicada.
	$datos = mysqli_query($enlace, $sql); // Ejecución de la selección previamente contemplada.
	/* Impresión de los valores de la base de datos en la tabla */
	while ($campo = mysqli_fetch_array($datos))
	{
		echo "<TR>
			<TD>".$campo['id']."</TD>
			<TD>".$campo['ledstat']."</TD>
		       </TR>";
	}
?>
