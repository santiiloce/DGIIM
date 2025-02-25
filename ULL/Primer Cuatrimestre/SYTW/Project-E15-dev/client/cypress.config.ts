import { defineConfig } from 'cypress';


export default defineConfig({
  e2e: {
    baseUrl: 'http://localhost:5173', // Cambia según tu servidor
    supportFile: false,
    specPattern: 'cypress/e2e/**/*.cy.{js,jsx,ts,tsx}',
    pageLoadTimeout: 120000,
  },
  component: {
    devServer: {
      framework: 'vue',
      bundler: 'webpack',
    },
  },
});
