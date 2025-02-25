

describe('Test de Integración - Log out', () => {
    beforeEach(() => {
      cy.intercept('GET', '**/*.js', { statusCode: 200, body: '' });
      cy.visit('/login');
    });
  
  
    it('Debe cerrar sesión correctamente', () => {
        cy.get('input#email').type('juan@juan.com'); // Cambia el selector
        cy.get('input#password').type('juan');        
      cy.get('button[type="submit"]').click(); // Haz clic en el botón de login
  
  
      // Verifica que el usuario sea redirigido
      cy.url().should('include', '/'); // Verifica la URL
      cy.get('.logout').click(); // Haz clic en el botón de logout
      cy.contains('Iniciar Sesión').should('be.visible'); // Verifica un mensaje en el dashboard
      cy.contains('Registrarse').should('be.visible'); // Verifica un mensaje en el dashboard
    });
  });