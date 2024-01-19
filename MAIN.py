import psycopg2

def buscar_usuario_por_nombre(cursor, nombre):

    try:
    
        with cursor() as cursor:
            cursor.execute("SELECT * FROM \"Clientes\" WHERE \"Nombre\" = %s;", (nombre,))
            resultados = cursor.fetchall()
            return resultados
    
    except Exception as e:
        print(f"Error al buscar usuario por nombre: {e}")
        return None

def buscar_usuario_por_telefono(cursor, telefono):
    try:
        with cursor() as cursor:
            cursor.execute("SELECT * FROM \"Clientes\" WHERE \"Telefono\" = %s;", (telefono,))
            resultados = cursor.fetchall()
            return resultados
    except Exception as e:
        print(f"Error al buscar usuario por teléfono: {e}")
        return None


def ingresar_usuario(conn, nombre, telefono, direccion, asunto, experiencia):
    try:
        with conn.cursor() as cursor:
            cursor.execute("INSERT INTO \"Clientes\" (\"Nombre\", \"Telefono\", \"Direccion\", \"Asunto\", \"Experiencia\") VALUES (%s, %s, %s, %s, %s);",
                           (nombre, telefono, direccion, asunto, experiencia))
        conn.commit()
        print("Usuario ingresado exitosamente.")
    except Exception as e:
        print(f"Error al ingresar usuario: {e}")

def main():
    try:
        # Conectar a la base de datos
        conn = psycopg2.connect(
            host="heffalump.db.elephantsql.com",
            user="kenwruxs",
            password="RjL5PaB8Ofh7YYppLbT7hh1nfIandhQn",
            database="kenwruxs"
        )

        while True:
            # Mostrar menú
            print("\nMenú:")
            print("1. Buscar usuario por nombre")
            print("2. Buscar usuario por teléfono")
            print("3. Ingresar nuevo usuario")
            print("4. Salir")

            opcion = input("Seleccione una opción (1-4): ")

            if opcion == "1":
                nombre_a_buscar = input("Ingrese el nombre del usuario a buscar: ")
                resultados_nombre = buscar_usuario_por_nombre(conn.cursor, nombre_a_buscar)
                print("Resultados por nombre:")
                for row in resultados_nombre:
                    print(row)
            elif opcion == "2":
                telefono_a_buscar = input("Ingrese el teléfono del usuario a buscar: ")
                resultados_telefono = buscar_usuario_por_telefono(conn.cursor, telefono_a_buscar)
                print("Resultados por teléfono:")
                for row in resultados_telefono:
                    print(row)
            elif opcion == "3":

                nombre = input("Ingrese el nombre del nuevo usuario: ")
                
                telefono = input("Ingrese el teléfono del nuevo usuario: ")
                
                direccion = input("Ingrese la dirección del nuevo usuario: ")
                
                asunto = input("Ingrese el asunto del nuevo usuario: ")
                
                experiencia = input("Ingrese la experiencia del nuevo usuario: ")
                
                ingresar_usuario(conn, nombre, telefono, direccion, asunto, experiencia)
            
            elif opcion == "4":
                print("Saliendo del programa.")
                break
            else:
                print("Opción no válida. Por favor, seleccione una opción del 1 al 4.")

    except Exception as e:
        print(f"Error general: {e}")

    finally:
        # Cerrar la conexión al salir del programa
        conn.close()

if __name__ == "__main__":
    main()
