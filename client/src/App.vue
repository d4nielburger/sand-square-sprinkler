<script setup>
import GaragePumpControl from './components/GaragePumpControl.vue';
import TankFillSelection from './components/TankFillSelection.vue';
import SprinklerControl from './components/SprinklerControl.vue';
import HoseControl from './components/HoseControl.vue';
import StatusDisplay from './components/StatusDisplay.vue';
</script>

<template>
  <div id="app">
    <div class="main-element">
      <StatusDisplay/>
    </div>
    <div id="control" class="main-element">
      <h2>Controls</h2>
      <GaragePumpControl/>
      <TankFillSelection/>
      <SprinklerControl/>
      <HoseControl/>
    </div>
  </div>
</template>

<style scoped>
.main-element{
  padding: 2em;
}
</style>