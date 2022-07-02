<?PHP
error_reporting(E_ALL ^ E_WARNING); // Oculta ciertas advertencias.
$ledstat = $_GET['ledstat'];
$enlace = mysqli_connect('127.0.0.1', 'root', '', 'conexion') // Intenta establecer la conexión con la base de datos.
or die('No se puede conectar: '. mysqli_connect_error()); // Si el intento de conexión fallara, brindaría esta información.
/* Si llegara a conectarse, enviaría la siguiente información. */
echo 'Conexión Exitosa. <BR />';
echo 'Dato:	'.$ledstat;
echo '<hr />';
/* El valor alojado en "ledstat" es registrado en una entrada de la base de datos. */
$consulta = mysqli_query($enlace, "INSERT INTO ledstatus(ledstat) VALUES ('$ledstat')");
/* Si no pudiera efectuarse lo anterior, debería aparecer: */
if(!$consulta) {
echo "Error al guardar. <BR />";
}
/* En su defecto; o sea, si el valor de "ledstat" se hubiera registrado, aparecería: */
else {
echo "Datos Guardados. <BR />";
}
/* Impresión por pantalla de los datos (ordenados en una tabla). */
echo "<HR />";
echo "Registro de la base de datos: <BR />";
echo "<HR />";
echo "<TABLE BORDER=1> 
	<TR>
	<TD> ID </TD>
	<TD> Dato </TD>
	</TR>";
$sql = "SELECT * FROM ledstatus";
$datos = mysqli_query($enlace,$sql);
while($campo = mysqli_fetch_array($datos)) 
{
echo "<TR>
	<TD>".$campo['id']."</TD>
	<TD>".$campo['ledstat']."</TD>
	</TR>"	;
}
?>