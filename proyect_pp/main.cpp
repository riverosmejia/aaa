#include <iostream>
#include <pqxx/pqxx>

void buscarPorNombre(pqxx::connection &conn) {
    std::string nombre;
    std::cout << "Ingrese el nombre a buscar: ";
    std::cin.ignore();  // Limpiar el buffer
    std::getline(std::cin, nombre);

    pqxx::work txn(conn);
    pqxx::result result = txn.exec("SELECT * FROM \"Clientes\" WHERE \"Nombre\" = " + txn.quote(nombre));

    // Imprimir resultados
    for (const pqxx::tuple &row : result) {
        for (const auto &field : row) {
            std::cout << field.c_str() << " ";
        }
        std::cout << std::endl;
    }

    // Finalizar la transacción
    txn.commit();
}


void buscarPorTelefono(pqxx::connection &conn) {
    std::string telefono;
    std::cout << "Ingrese el teléfono a buscar: ";
    std::cin.ignore();  // Limpiar el buffer
    std::getline(std::cin, telefono);

    pqxx::work txn(conn);
    pqxx::result result = txn.exec("SELECT * FROM \"Clientes\" WHERE \"Telefono\" = " + txn.quote(telefono));

    // Imprimir resultados
    for (const auto &row : result) {
        for (const auto &field : row) {
            std::cout << field.c_str() << " ";
        }
        std::cout << std::endl;
    }

    // La transacción implícita se comprometerá automáticamente al salir del bloque pqxx::work
}

void ingresarCliente(pqxx::connection &conn) {
    std::string nombre, telefono, direccion, asunto, experiencia;

    std::cout << "Ingrese el nombre del cliente: ";
    std::cin.ignore();
    std::getline(std::cin, nombre);

    std::cout << "Ingrese el teléfono del cliente: ";
    std::getline(std::cin, telefono);

    std::cout << "Ingrese la dirección del cliente: ";
    std::getline(std::cin, direccion);

    std::cout << "Ingrese el asunto del cliente: ";
    std::getline(std::cin, asunto);

    std::cout << "Ingrese la experiencia del cliente: ";
    std::getline(std::cin, experiencia);

    pqxx::work txn(conn);
    txn.exec("INSERT INTO \"Clientes\" (\"Nombre\", \"Telefono\", \"Direccion\", \"Asunto\", \"Experiencia\") "
             "VALUES (" + txn.quote(nombre) + ", " + txn.quote(telefono) + ", " +
             txn.quote(direccion) + ", " + txn.quote(asunto) + ", " + txn.quote(experiencia) + ")");

    std::cout << "Cliente ingresado exitosamente.\n";

    // Finalizar la transacción
    txn.commit();
}

int main() {
    try {
        // Conexión a la base de datos
        pqxx::connection conn("dbname=your_database user=your_user password=your_password hostaddr=your_host");

        // Menú de opciones
        int opcion;
        do {
            std::cout << "\nMenú:\n";
            std::cout << "1. Buscar por nombre\n";
            std::cout << "2. Buscar por teléfono\n";
            std::cout << "3. Ingresar cliente\n";
            std::cout << "4. Salir\n";
            std::cout << "Ingrese la opción: ";
            std::cin >> opcion;

            switch (opcion) {
                case 1:
                    buscarPorNombre(conn);
                    break;
                case 2:
                    buscarPorTelefono(conn);
                    break;
                case 3:
                    ingresarCliente(conn);
                    break;
                case 4:
                    std::cout << "Saliendo del programa.\n";
                    break;
                default:
                    std::cout << "Opción no válida. Inténtelo de nuevo.\n";
            }
        } while (opcion != 4);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
