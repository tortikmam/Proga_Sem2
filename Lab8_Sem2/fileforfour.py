import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Загрузка данных
data = pd.read_csv('results.csv')

# Создание графика
plt.figure(figsize=(12, 8))
sns.lineplot(data=data, x='matrix_size', y='execution_time_ms', 
             hue='threads_count', palette='Set1', marker='o')

plt.title('Matrix Multiplication Performance')
plt.xlabel('Matrix Size (N x N)')
plt.ylabel('Execution Time (ms)')
plt.grid(True)
plt.legend(title='Threads Count')
plt.tight_layout()

# Сохранение графика
plt.savefig('performance_graph.png', dpi=300)
plt.show()