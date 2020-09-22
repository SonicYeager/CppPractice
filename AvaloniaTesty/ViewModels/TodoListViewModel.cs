using System;
using System.Collections.Generic;
using AvaloniaTesty.Models;
using System.Collections.ObjectModel;

namespace AvaloniaTesty.ViewModels
{
    public class TodoListViewModel : ViewModelBase
    {
        public TodoListViewModel(IEnumerable<TodoItem> items)
        {
            Items = new ObservableCollection<TodoItem>(items);
        }

        public ObservableCollection<TodoItem> Items { get; }
    }
}
