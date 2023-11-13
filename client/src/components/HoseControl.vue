<template>
    <div>
      <h3>HoseControl</h3>
      <button @click="hoseOn">Hose On</button>
      <button @click="hoseOff">Hose Off</button>
    </div>
  </template>
  
  <script>
  const API_URI = 'http://localhost:3000/sss/api';
  
  export default {
    methods: {
      async hoseOn() {
        try {
          await fetch(`${API_URI}/control/hose`, {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({ state: 'on' }),
          });
        } catch (error) {
          console.error('Error:', error);
        }
      },
      async hoseOff() {
        try {
          await fetch(`${API_URI}/control/hose`, {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({ state: 'off' }),
          });
        } catch (error) {
          console.error('Error:', error);
        }
      },
    },
  };
  </script>
  
  <style scoped>
  /* Your CSS here */
  </style>
  