<template>
    <div>
      <h3>Sprinkler Control</h3>
      <button @click="sprinklerOn">Sprinkler On</button>
      <button @click="sprinklerOff">Sprinkler Off</button>
    </div>
  </template>
  
  <script>
  const API_URI = 'http://localhost:3000/sss/api';
  
  export default {
    methods: {
      async sprinklerOn() {
        try {
          await fetch(`${API_URI}/control/sprinkler`, {
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
      async sprinklerOff() {
        try {
          await fetch(`${API_URI}/control/sprinkler`, {
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
  