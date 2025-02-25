// Importa comandos personalizados (si existen)
import './commands';


// Manejar errores globales en Cypress
Cypress.on('uncaught:exception', (err, runnable) => {
  // Ignora errores no controlados específicos si no afectan las pruebas
  console.log('Error capturado:', err.message);
  return false; // Evita que el test falle
});


// Configuración para todos los tests
beforeEach(() => {
  // Configuración que se ejecutará antes de cada prueba
  cy.log('Iniciando prueba...');
});






