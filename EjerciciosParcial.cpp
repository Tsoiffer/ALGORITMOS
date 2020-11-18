/* Ejercicio 1 (ítems 0, 1, 2, 3 y 4)

Se quiere almacenar en memoria los gastos efectuados por cada uno de los 15 sectores  de una empresa en un mes determinado para realizar un análisis estádístico.
 Para ello se implementará una matriz de listas, donde las filas representan los sectores y las columnas los días y cada elemento es la lista con cada gasto de ese sector en ese día.
Los datos para armar la estructura se encuentran en el archivo de datos binario  “Gastos.dat”, donde cada registro representa un gasto efectuado y tiene:
-	 Número de sector (de 1 a 15)
-	Día del mes (de 1 a 31)
-	Detalle
-	Importe gastado.
El archivo no está ordenado y puede tener varios gastos realizados por un mismo sector.

0)	Función armarEstructura debe generar la estructura en memoria con los datos del archivo, tener en cuenta que la estructura hay que utilizarla en las otras funciones. Desarrollar todas las funciones utilizadas.

1)	Función mostrarGastos debe mostrar por pantalla el siguiente listado:
		Sector 1
			Día 1
				…..  (detalle e importe de cada gasto)
				…..
			Día 2	
				…..
		Sector 2
			…..
Detalle e importe de cada gasto (ordenado de mayor a menor por importe) agrupado por sector y por día. 
Desarrollar todas las funciones utilizadas.

2)	Función mostrarGastosSector debe mostrar número de sector y sus gastos totales acumulados en el mes.

3)	Función mostrarGastos1Quincena debe mostrar los datos acumulados en la primera quincena (del día 1 al día 14 incluidos)

4)	Función mayorGasto debe mostrar qué sector y qué día se realizó el mayor gasto (suponer único)


Ejercicio 2 (ítems 5, 6, 7, 8 y 9)

Una entidad bancaria ofrece diferentes tipos de créditos (personal, hipotecario, etc.).
Se quiere hacer un programa para administrar la asignación de los mismos a las personas que los requieran y mostrar datos estadísticos.
Los créditos se asignan según los ingresos que han declarado, teniendo prioridad aquellos que tengan el mayor ingreso promedio.
Se utilizará una lista de créditos con sublista de inscriptos al crédito.
Se cuenta con el archivo de datos (binario) “Inscriptos.dat” con un registro por cada persona que se ha inscripto para solicitar un crédito, con el siguiente diseño de registro:
	Dni
	Apellido y nombre
	Código del crédito que solicita
	Ingreso Promedio

5) Función ingresarCreditos
El usuario del programa deberá ingresar los diferentes créditos que ofrece la entidad (código y descripción del crédito) y la cantidad de personas máxima a los que se les otorgará el mismo (cupo). Con estos datos deberá preparar la estructura para almacenar, luego, los inscriptos. El ingreso de datos finaliza con código de crédito cero. Tener en cuenta que la estructura hay que utilizarla en las otras funciones
Desarrollar todas las funciones utilizadas.

6) Función organizarInscriptos
Procesar los datos del archivo, almacenándolos convenientemente en la estructura de datos para realizar la asignación de los créditos. Tener en cuenta que la estructura hay que utilizarla en las otras funciones.
Desarrollar todas las funciones utilizadas.

7) Función mostrarCreditoMayor
Informar código y descripción de crédito en el que hubo la mayor cantidad de inscriptos (suponer único)
Desarrollar todas las funciones utilizadas.

 8) Función mostrarCreditosVacios
Informar código y descripción de crédito, ordenado por código de crédito de aquellos en los que no hubo inscriptos.
Desarrollar todas las funciones utilizadas.

9) Función mostrarListado de inscriptos asignados
Mostrar por cada crédito, ordenado por código: dni, apellido y nombre de cada persona a la que se le ha otorgado el crédito.
Se le otorga el crédito a la cantidad de personas que se inscribieron para ese crédito o la cantidad máxima posible, según criterio de asignación. Ejemplo: si el crédito tiene un cupo de 10 personas y se inscribieron 8 se le otorgará a los 8, si el crédito tiene un cupo de 10 y se inscribieron 15, se le otorgará a los 10 de mayor sueldo, o sea hay que mostrar, los 10 de mayor sueldo.
Desarrollar todas las funciones utilizadas.

*/
