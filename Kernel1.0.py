import time
import random

class Proceso:
    def __init__(self, pid, nombre, tiempo_total):
        self.pid = pid
        self.nombre = nombre
        self.tiempo_restante = tiempo_total

    def ejecutar(self, quantum):
        if self.tiempo_restante > 0:
            tiempo_ejecucion = min(quantum, self.tiempo_restante)
            self.tiempo_restante -= tiempo_ejecucion
            print(f"[PID {self.pid}] Ejecutando {self.nombre} por {tiempo_ejecucion}s | Restante: {self.tiempo_restante}s")
            time.sleep(0.5)

class Kernel:
    def __init__(self):
        self.procesos = []
        self.pid_counter = 1

    def crear_proceso(self, nombre, tiempo):
        proceso = Proceso(self.pid_counter, nombre, tiempo)
        self.procesos.append(proceso)
        print(f"Proceso creado: {nombre} (PID {self.pid_counter})")
        self.pid_counter += 1

    def scheduler_round_robin(self, quantum=1):
        print("\n--- Iniciando Scheduler Round Robin ---\n")
        while any(p.tiempo_restante > 0 for p in self.procesos):
            for proceso in self.procesos:
                if proceso.tiempo_restante > 0:
                    proceso.ejecutar(quantum)
        print("\n--- Todos los procesos terminaron ---")

# Simulación
kernel = Kernel()
kernel.crear_proceso("Navegador", random.randint(2,5))
kernel.crear_proceso("Editor", random.randint(2,5))
kernel.crear_proceso("ServicioRed", random.randint(2,5))

kernel.scheduler_round_robin()