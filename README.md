# **qaria**
**Project of the Object Programming course of the University of Padua**

## Model Description

### Hierarchies and inheritance
The model starts from the AtmosphericEvent class, which represents all the information common to events. The three subclasses Snow, Rain, and HailStorm represent the actual atmospheric events, by means of an is-a relationship, and apply the parameters related to the atmospheric event.
There are two model types: DataModel and AtmosphericEventModel. The first is used to manage data within CSV files, the second to filter events and their type. Additionally, both model and data management classes and views extend pre-existing classes to the Qt framework to ensure consistency to the methods present. There are also delegated classes that apply the well-known Visitor design pattern in the use of data visualization related to the specific atmospheric event, making it possible to display specific according to the required context.
Classes protect their information from external access, allowing secure access to variables that allow graphical management of atmospheric events to be displayed based on the specific type as described.
Instead of having four separate files to represent the parent class and its subclasses, they are declared inside the atmophericevent.cpp file, without compromising their operation or inheritance. However, each class has its own behavior that is logically independent of the others, in order to logically separate the responsibilities of each and manage events in a virtual and extensible manner.

## Polymorphism
In the realization of the qaria project, the non-trivial use of polymorphism is mainly evident between the father class AtmosphericEvent and its daughter classes. In particular, it was used for the creation of the widget that displays the event information, which is graphically opened as a drop-down menu and as a table, allowing in both cases the precise modification of the present type.
The use of polymorphism occurs exclusively during the visualization phase. When you expand the dropdown based on the selected event, the appropriate details for the specific are displayed; the same goes for the widget that displays the correct information for the selected one.
In addition, the management of the CSV file also involves the use of extensible methods for the management of its data components and for the data shown after the views based on the changes made on the model.
It is planned to create a hierarchy of delegated classes with DataDelegate as their parent class in order to allow communication and linking between the updated data in the model and what is shown within the widget. For the latter, we can specify a series of delegated daughter classes, referring to each type of atmospheric event (specifically, SnowDelegate, RainDelegate and HailStormDelegate) in order to manage, through a special virtual draw method, the update of the data from the model in the specific view to the requested event.

### Non-trivial polymorphism
To make the use of polymorphism non-trivial, the DataDelegate class implements a method called draw, which draws a custom widget when an event is selected from the list. This method allows you to show not only the values common to all event classes, but also those specific to each class. Additionally, to highlight the use of polymorphism, an icon is displayed that represents the atmospheric event using the imagePath m attribute in AtmosphericEvent.
This approach leverages polymorphism in a significant way, allowing each subclass of AtmosphericEvent to define its own delegate to display event-specific information and icon. This provides greater flexibility and extensibility to the system, as new event classes can be easily added and dynamically managed by the display widget.

## Persistence of data
The CSV format is used to save information, so that you can allow events to be shared with other users; in fact, it is possible to import or create new files from scratch, in order to catalog the data in the best possible way and then manage their information.
An example of the data structure is made available by the data.csv file attached in the delivery, which can be uploaded to the program easily by selecting the appropriate option.

### Creating, Modifying, and Deleting Objects
To create a new object, simply right-click on a row and select where to place it, particularly above or below the selected one.
Deletion is possible using the same reasoning. If I select the row, I can decide whether to delete it by selecting from the pop-up menu.
To edit the information, simply double-click the cells. In this case, it should be noted that there is a Qt bug on macOS as it is, when the two QComboBoxes used to select the event and the danger are invoked, it remains visible under the previous choice. This behavior does not occur on other platforms.

## Container for objects in the hierarchy
It was decided to develop a linked list structure to be used as a hierarchy container, given its extensible for new computing operations. In this case, before being saved to the CSV file, the various weather events are saved locally on the linked list and then, once the user decides to save the data, they are written to the CSV file. Additionally, custom methods for searching, deleting, editing, and adding objects have been implemented in the container.

## Functionality and GUI

### Functionality
The features implemented are, for simplicity, divided into two macro-categories: structural, that is, those that make up the heart of the program, and aesthetic, those that allow easy use.

#### Structural Capabilities
- Create, open, save and overwrite a CSV file.
- Search by type and danger of the event.
- Addition of atmospheric events.
- Deletion of individual events.
- Filters for results

#### Aesthetic features
- Menu bar.
- Checking for unsaved changes.
- Use of icons in buttons.
- Minimum size of the window.
- Detail view of the events.
