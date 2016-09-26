#include "pmd-datagen.h"
// using namespace std;
using namespace DDS;

PmdDatagen::PmdDatagen(QObject* parent): QObject(parent)
{
    ecgData <<0<<0<<0<<0<<-11<<-9<<-8<<-4<<0<<-1<<3<<7<<8<<12<<13<<12<<7<<5<<-3<<-7<<-12<<-13<<-16<<-12<<-13<<-13<<-13<<-14<<-14<<-12<<-13<<-13<<-13<<-14<<-15<<-16<<-16<<-17<<-14<<-15<<-8<<-17<<-16<<1<<44<<72<<96<<80<<31<<-11<<-16<<-13<<-12<<-13<<-15<<-16<<-17<<-19<<-17<<-16<<-16<<-15<<-14<<-13<<-14;
    abpData <<-7 << -1 <<11 <<24 <<35 <<46 <<55 <<63 <<72 <<79 <<85 << 92 << 98 <<102 <<102 <<103<<103 <<102 <<101 << 97 << 93 << 88 <<83 <<78 <<75 <<66 <<63 <<63 <<63 <<64 <<66 <<67 << 68 <<68<<67 << 64 << 58 <<50 <<49 <<42 <<38 <<33 <<29 <<26 << 24 << 22 << 20 <<18 <<16 <<14 <<13 <<11 <<10<<9 <<7 <<6 << 5 <<3 <<2 <<1 << 0 <<-1 <<-1 <<-2 <<-2 <<-2 <<-3 <<-3 <<-3 <<-4 <<-4 << -4<<-5 <<-5 <<-5 <<-6 <<-6 <<-6 << -6 << -6 <<-7 <<-7 << -7 <<-7<<-5<<-5;
    plethData <<-7 << -1 <<11 <<24 <<35 <<40 <<46 <<50 <<55 <<58 <<63 <<72 <<74 << 74 << 76<<78 <<80 << 81 << 81 <<81 <<80 <<80<<80 <<79 <<79 << 78 << 76 << 74 << 70 <<66 <<63 <<63 <<63 <<64 <<66 <<67 << 68 <<68<<67 << 64 << 58 <<50 <<49 <<42 <<38 <<33 <<29 <<26 << 24 << 22 << 20 <<18 <<16 <<14 <<13 <<11 <<10<<9 <<7 <<6 << 5 <<3 <<2 <<1 << 0 <<-1 <<-1 <<-2 <<-2 <<-2 <<-3 <<-3 <<-3 <<-4 <<-4 << -4<<-5 <<-5 <<-5 <<-6 <<-6 <<-6 << -6 << -6 <<-7 <<-7 << -7 <<-7<<-8<<-9<<-9;
    ecgIndex =-1;
    abpIndex =-1;
    plethIndex=-1;
    pm_data.index=0;

	// Initialize DDS vars
    participant = NULL;
    publisher = NULL;
    topic = NULL;
    writer = NULL;
	domainId = 0;
	type_name = NULL;
	pm_data_struct_writer = NULL;
	instance = NULL;
    instance_handle = HANDLE_NIL;

	// Create DDS participant
    participant = TheParticipantFactory->create_participant(
        domainId, PARTICIPANT_QOS_DEFAULT,
        NULL /* listener */, STATUS_MASK_NONE);
    if (participant == NULL) {
        printf("create_participant error\n");
        return;
    }

    /* To customize publisher QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    publisher = participant->create_publisher(
        PUBLISHER_QOS_DEFAULT, NULL /* listener */, STATUS_MASK_NONE);
    if (publisher == NULL) {
        printf("create_publisher error\n");
		publisher_shutdown(participant);
        return;
    }

    /* Register type before creating topic */
    type_name = DataBus::pm_data_structTypeSupport::get_type_name();
    retcode = DataBus::pm_data_structTypeSupport::register_type(
        participant, type_name);
    if (retcode != RETCODE_OK) {
        printf("register_type error %d\n", retcode);
        publisher_shutdown(participant);
        return;
    }

    /* To customize topic QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    topic = participant->create_topic(
        "Example DataBus_pm_data_struct",
        type_name, TOPIC_QOS_DEFAULT, NULL /* listener */,
        STATUS_MASK_NONE);
    if (topic == NULL) {
        printf("create_topic error\n");
        publisher_shutdown(participant);
        return;
    }

    /* To customize data writer QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    writer = publisher->create_datawriter(
        topic, DATAWRITER_QOS_DEFAULT, NULL /* listener */,
        STATUS_MASK_NONE);
    if (writer == NULL) {
        printf("create_datawriter error\n");
        publisher_shutdown(participant);
        return;
    }
    pm_data_struct_writer = DataBus::pm_data_structDataWriter::narrow(writer);
    if (pm_data_struct_writer == NULL) {
        printf("DataWriter narrow error\n");
        publisher_shutdown(participant);
        return;
    }

    /* Create data sample for writing */
    instance = DataBus::pm_data_structTypeSupport::create_data();
    if (instance == NULL) {
        printf("DataBus::pm_data_structTypeSupport::create_data error\n");
        publisher_shutdown(participant);
        return;
    }

	timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateData()));
    timer->setInterval(30);
    timer->start();
}

PmdDatagen::~PmdDatagen()
{
    ecgData.clear();
    abpData.clear();
    plethData.clear();
	// publisher_shutdown(participant);
}

void PmdDatagen::connectionStatus()
{
	printf("ConnectionStatus Slot entered\n");
}

unsigned int PmdDatagen::getECGData()
{
    if (ecgIndex == ecgData.count()-1)
        ecgIndex = -1;

    ecgIndex++;
    return ecgData[ecgIndex];
}

unsigned int PmdDatagen::getABPData()
{
    if (abpIndex == abpData.count()-1)
        abpIndex = -1;

    abpIndex++;
    return abpData[abpIndex];
}

unsigned int PmdDatagen::getPlethData()
{
    if (plethIndex == plethData.count()-1)
        plethIndex = -1;

    plethIndex++;
    return plethData[plethIndex];
}

void PmdDatagen::updateData()
{
	int i = pm_data.index % 66;
	if ( i == 0 )
		printf("PmdDatagen::updateData() - %d\n", pm_data.index);
    if (pm_data.index == USHRT_MAX)
    {
        pm_data.index=0;
    }
    else
    {
        pm_data.index++;
    }

    pm_data.ecgValue = getECGData();
    pm_data.abpValue = getABPData();
    pm_data.plethValue = getPlethData();
    
	// Send data here
	instance->ecgValue = getECGData();
	instance->abpValue = getABPData();
    instance->plethValue = getPlethData();

	retcode = pm_data_struct_writer->write(*instance, instance_handle);
	if (retcode != RETCODE_OK) {
		printf("write error %d\n", retcode);
	}	
}

int PmdDatagen::publisher_shutdown(DomainParticipant *participant) {
    ReturnCode_t retcode;
    int status = 0;

    if (participant != NULL) {
        retcode = participant->delete_contained_entities();
        if (retcode != RETCODE_OK) {
            printf("delete_contained_entities error %d\n", retcode);
            status = -1;
        }

        retcode = TheParticipantFactory->delete_participant(participant);
        if (retcode != RETCODE_OK) {
            printf("delete_participant error %d\n", retcode);
            status = -1;
        }
    }
    /* RTI Connext provides finalize_instance() method on
    domain participant factory for people who want to release memory used
    by the participant factory. Uncomment the following block of code for
    clean destruction of the singleton. */
    /*
    retcode = DomainParticipantFactory::finalize_instance();
    if (retcode != RETCODE_OK) {
        printf("finalize_instance error %d\n", retcode);
        status = -1;
    }
    */

    return status;
}
